#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <fstream>

#include "../Model/level.h"
#include "../Model/enemy.h"
#include "../Service/movementservice.h"

using namespace std;
using namespace chrono;

class MovementBenchmark{

    private:

        void MoveEnemiesSingleThread(vector<Enemy>& enemies, Level& level){

            for (auto& enemy : enemies){

                Point originalPosition = enemy.GetCoordinate();
                enemy.Update();
                MoveCreature(enemy, level, enemy.GetDirection());
                
                if (originalPosition.x == enemy.GetCoordinate().x && originalPosition.y == enemy.GetCoordinate().y){

                    enemy.SwitchDirection(enemy.GetDirection());

                }

            }

        }
        
        void MoveEnemiesMultiThread(vector<Enemy>& enemies, Level& level, int threadCount){

            if (threadCount <= 1){

                MoveEnemiesSingleThread(enemies, level);
                return;

            }
            
            vector<thread> threads;
            size_t chunkSize = enemies.size() / threadCount;
            
            for (int i = 0; i < threadCount; ++i){

                auto start = enemies.begin() + (i * chunkSize);
                auto end = (i == threadCount - 1) ? enemies.end() : start + chunkSize;
                
                threads.emplace_back([start, end, &level](){

                    for (auto it = start; it != end; ++it){

                        Point originalPosition = it->GetCoordinate();
                        it->Update();
                        MoveCreature(*it, level, it->GetDirection());
                        
                        if (originalPosition.x == it->GetCoordinate().x && originalPosition.y == it->GetCoordinate().y){

                            it->SwitchDirection(it->GetDirection());

                        }

                    }

                });
            }
            
            for (auto& t : threads){

                t.join();

            }

        }

    public:
    
        void RunBenchmark(){
            
            vector<size_t> enemyCounts = {10, 100, 1000, 10000, 100000, 1000000};
            const int iterations = 1000;
            
            unsigned int hwThreads = thread::hardware_concurrency();
            if (hwThreads == 0) hwThreads = 4;
            
            ofstream csv("benchmark_results.csv");
            csv << "enemy_count,single_thread_ms,multi_thread_ms,single_enemies_sec,multi_enemies_sec,threads\n";
            
            cout << "Threads available: " << hwThreads << "\n\n";
            
            for (size_t enemyCount : enemyCounts){

                cout << "--- " << enemyCount << " ENEMIES ---\n";
                
                Level level(3); 
                level.GenerateEnemies(enemyCount); 
                vector<Enemy>& enemies = level.GetEnemies();
                
                vector<double> times(2, 0.0);
                
                for (int mode = 0; mode < 2; ++mode){

                    string modeName = (mode == 0) ? "SINGLE" : "MULTI";
                    cout << modeName << ": ";
                    
                    for (int warmup = 0; warmup < 3; ++warmup){

                        MoveEnemiesSingleThread(enemies, level);

                    }
                    
                    auto start = high_resolution_clock::now();
                    for (int i = 0; i < iterations; ++i){

                        if (mode == 0){

                            MoveEnemiesSingleThread(enemies, level);

                        } else {

                            MoveEnemiesMultiThread(enemies, level, hwThreads);

                        }

                    }
                    
                    auto end = high_resolution_clock::now();
                    
                    times[mode] = duration_cast<milliseconds>(end - start).count() / (double)iterations;
                    cout << fixed << setprecision(2) << times[mode] << " ms\n";

                }
                
                double singleEnemiesSec = (enemies.size() * 1000.0) / times[0];
                double multiEnemiesSec = (enemies.size() * 1000.0) / times[1];
                
                csv << fixed << setprecision(3);
                csv << enemyCount << "," << times[0] << "," << times[1] << "," << singleEnemiesSec << "," << multiEnemiesSec << "," << hwThreads << "\n";
                
                cout << "Speedup: " << fixed << setprecision(1) << (times[0]/times[1]) << "x\n\n";

            }
            
            csv.close();
            cout << "===============================================\n";
            cout << "CSV saved: benchmark_results.csv\n";
            cout << "Run: python3 plot_demo.py\n";

        }

};

int main(){

    srand(42);
    MovementBenchmark benchmark;
    benchmark.RunBenchmark(); 
    return 0;

}
