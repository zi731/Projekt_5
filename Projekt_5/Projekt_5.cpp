﻿/// @file Projekt_5.cpp Plik główny projektu
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

/// @brief Obliczanie wartości liczby PI dla danego segmentu przedziałów.
/// @param[in] start Pierwszy przedział segmentu
/// @param[in] end Ostatni przedział segmentu
/// @param[in] num_intervals Liczba przedziałów
/// @param sum Suma wartości liczby PI
/// @param step Szerokość przedziału
/// @param x Środek przedziału
/// @return Wartość PI danego segmentu
double calculate_pi_segment(int start, int end, int num_intervals) {
	double sum = 0.0;
	double step = 1.0 / num_intervals;
	for (int i = start; i < end; ++i) {
		double x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
    }
    return sum * step;
}

/// @brief Część główna programu.
/// @param num_intervals Liczba przedziałów całki
/// @param num_threads Liczba wątków
/// @param start_time Początkowy czas obliczeń
/// @param threads Wektor wątków
/// @param results Wektor wyników dla każdego wątku
/// @param intervals_per_thread Liczba przedziałów na wątek
/// @param start Pierwszy przedział segmentu
/// @param end Ostatni przedział segmentu
/// @param pi Przybliżona wartość liczby PI
/// @param end_time Końcowy czas obliczeń
/// @param duration Czas obliczeń
int main() {
	int num_intervals, num_threads;

    std::cout << "Podaj liczbe przedzialow calki: ";
    std::cin >> num_intervals;
    std::cout << "Podaj liczbe watkow: ";
    std::cin >> num_threads;

	auto start_time = std::chrono::high_resolution_clock::now();

	std::vector<std::thread> threads;
	std::vector<double> results(num_threads, 0.0);
	int intervals_per_thread = num_intervals / num_threads;

	for (int i = 0; i < num_threads; ++i) {
		int start = i * intervals_per_thread;
		int end = (i == num_threads - 1) ? num_intervals : start + intervals_per_thread;
		threads.emplace_back([&results, i, start, end, num_intervals]() {
			results[i] = calculate_pi_segment(start, end, num_intervals);
            });
    }

	for (auto& t : threads) {
		t.join();
    }

	double pi = 0.0;
	for (const auto& result : results) {
		pi += result;
    }

	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Przyblizona wartosc PI: " << pi << std::endl;
    std::cout << "Czas obliczen: " << duration.count() << " sekund" << std::endl;

    return 0;
}
/*
W tym programie:
1.	Użytkownik podaje liczbę przedziałów całki oraz liczbę wątków.
2.	Program dzieli obliczenia na segmenty, które są przetwarzane równolegle przez wątki.
3.	Każdy wątek oblicza sumę dla swojego segmentu przedziałów.
4.	Wyniki są sumowane, aby uzyskać przybliżoną wartość liczby PI.
5.	Program mierzy czas obliczeń i wypisuje wynik oraz czas na ekran terminala.
Używam aktywnego dokumentu, ponieważ masz zaznaczoną odpowiednią opcję. Możesz dodać dodatkowy kontekst za pomocą # referencji.
*/