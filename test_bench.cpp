#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <numeric>

#include <vector>
#include <queue>
#include "LeonardoHeap.hpp"
#include "RelaxedLeonardoHeap.hpp"

constexpr int TIMES = 10;
constexpr int SIZE = 10000;

int A[SIZE];

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());

    {
        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
        std::cout << "| ascending input      | per insertion (avg. comparasions) | per deletion (avg. comparasions) |\n" ;

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| std priority queue   | " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::Heap<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| Leonardo Heap        | " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::RelaxedHeap<int, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| Relaxed Leonardo Heap| " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n\n";
    }

    {
        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
        std::cout << "| random input         | per insertion (avg. comparasions) | per deletion (avg. comparasions) |\n" ;

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (int i = 0; i < TIMES; i++) {
                std::shuffle(std::begin(A), std::end(A), gen);

                for (auto x : A)
                    pq.push(x);

                i_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;

                while (not pq.empty())
                    pq.pop();

                d_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;
            }

            std::cout << "| std priority queue   | "
                << std::left << std::setw(34) << i_cnt / (double)TIMES << "| "
                << std::left << std::setw(33) << d_cnt / (double)TIMES << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::Heap<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (int i = 0; i < TIMES; i++) {
                std::shuffle(std::begin(A), std::end(A), gen);

                for (auto x : A)
                    pq.push(x);

                i_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;

                while (not pq.empty())
                    pq.pop();

                d_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;
            }

            std::cout << "| Leonardo Heap        | "
                << std::left << std::setw(34) << i_cnt / (double)TIMES << "| "
                << std::left << std::setw(33) << d_cnt / (double)TIMES << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::RelaxedHeap<int, decltype(cmp)> pq(cmp);

            for (int i = 0; i < TIMES; i++) {
                std::shuffle(std::begin(A), std::end(A), gen);

                for (auto x : A)
                    pq.push(x);

                i_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;

                while (not pq.empty())
                    pq.pop();

                d_cnt += (double)sub_cnt / (double) SIZE;

                sub_cnt = 0;
            }

            std::cout << "| Relaxed Leonardo Heap| "
                << std::left << std::setw(34) << i_cnt / (double)TIMES << "| "
                << std::left << std::setw(33) << d_cnt / (double)TIMES << "|\n" ;
        }

        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n\n";
    }

    {
        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
        std::cout << "| descending input     | per insertion (avg. comparasions) | per deletion (avg. comparasions) |\n";

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);
            std::reverse(std::begin(A), std::end(A));

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| std priority queue   | " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);
            std::reverse(std::begin(A), std::end(A));

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::Heap<int, std::vector<int>, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| Leonardo Heap        | " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        {
            std::cout << "+----------------------+-----------------------------------+----------------------------------+\n";
            std::iota(std::begin(A), std::end(A), 0);
            std::reverse(std::begin(A), std::end(A));

            double i_cnt = 0.0;
            double d_cnt = 0.0;

            int sub_cnt = 0;
            auto cmp = [&sub_cnt] (const auto &a, const auto &b) { sub_cnt++; return a < b; };

            Leonardo::RelaxedHeap<int, decltype(cmp)> pq(cmp);

            for (auto x : A)
                pq.push(x);

            i_cnt += (double)sub_cnt / (double) SIZE;

            sub_cnt = 0;

            while (not pq.empty())
                pq.pop();

            d_cnt += (double)sub_cnt / (double) SIZE;

            std::cout << "| Relaxed Leonardo Heap| " << std::left << std::setw(34) << i_cnt << "| "<< std::left << std::setw(33) << d_cnt << "|\n" ;
        }

        std::cout << "+----------------------+-----------------------------------+----------------------------------+\n\n";
    }

    return 0;
}
