/// <summary> Algorytm wyliczania liczby PI metodą całkowania numerycznego z zastosowaniem GitHub Copilot
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

/// <summary>
/// Obliczanie wartości liczby PI dla danego segmentu przedziałów.
/// </summary>
/// <param name="start">Pierwszy przedział segmentu</param>
/// <param name="end">Ostatni przedział segmentu</param>
/// <param name="num_intervals">Liczba przedziałów</param>
/// <returns>Wartość PI danego segmentu</returns>
double calculate_pi_segment(int start, int end, int num_intervals) {
	double sum = 0.0; /// Suma wartości liczby PI
	double step = 1.0 / num_intervals; /// Szerokość przedziału
	for (int i = start; i < end; ++i) { /// Obliczanie sumy dla każdego przedziału w segmencie
		double x = (i + 0.5) * step; /// Środek przedziału
		sum += 4.0 / (1.0 + x * x); /// Obliczanie wartości liczby PI dla danego przedziału
    }
    return sum * step;
}

/// <summary>
/// Część główna programu.
/// </summary>
int main() {
	int num_intervals, num_threads; /// Liczba przedziałów całki i liczba wątków

	/// Pobieranie danych od użytkownika
    std::cout << "Podaj liczbe przedzialow calki: ";
    std::cin >> num_intervals;
    std::cout << "Podaj liczbe watkow: ";
    std::cin >> num_threads;

	auto start_time = std::chrono::high_resolution_clock::now(); /// Początkowy czas obliczeń

	std::vector<std::thread> threads; /// Wektor wątków
	std::vector<double> results(num_threads, 0.0); /// Wektor wyników dla każdego wątku
	int intervals_per_thread = num_intervals / num_threads; /// Liczba przedziałów na wątek

	for (int i = 0; i < num_threads; ++i) { /// Tworzenie wątków
		int start = i * intervals_per_thread; /// Pierwszy przedział segmentu
		int end = (i == num_threads - 1) ? num_intervals : start + intervals_per_thread; /// Ostatni przedział segmentu
		threads.emplace_back([&results, i, start, end, num_intervals]() { /// Wywołanie wątku
			results[i] = calculate_pi_segment(start, end, num_intervals); /// Obliczanie wartości liczby PI dla segmentu przedziałów
            });
    }

	for (auto& t : threads) { /// Oczekiwanie na zakończenie wszystkich wątków
		t.join(); /// Czekanie na zakończenie wątku
    }

	double pi = 0.0; /// Przybliżona wartość liczby PI
	for (const auto& result : results) { /// Sumowanie wyników z każdego wątku
		pi += result; /// Sumowanie wyników
    }

	auto end_time = std::chrono::high_resolution_clock::now(); /// Końcowy czas obliczeń
	std::chrono::duration<double> duration = end_time - start_time; /// Czas obliczeń

	/// Wyświetlanie wyników na ekranie terminala
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