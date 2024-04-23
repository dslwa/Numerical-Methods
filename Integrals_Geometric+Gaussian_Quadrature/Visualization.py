import matplotlib.pyplot as plt

# Dane osi x - liczba przedziałów
n_values = [1,2,4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]

# Dane osi y - obliczone wartości całki dla pierwszej metody
integral_values = [1.99499, 1.75077 ,1.69634 ,1.68311, 1.67982, 1.679 ,1.67879, 1.67874 ,1.67873 ,1.67873, 1.67873, 1.67873 ,1.67873]

# Dane osi y dla metody trapezów
trapezoid_values = [1.0779 ,1.53644, 1.64361 ,1.66997 ,1.67654 ,1.67818 ,1.67859, 1.67869 ,1.67872, 1.67872 ,1.67873 ,1.67873, 1.67873]

simpson_values = [1.68929, 1.67933 ,1.67876 ,1.67873, 1.67873, 1.67873, 1.67873, 1.67873, 1.67873, 1.67873, 1.67873, 1.67873 ,1.67873]
# Tworzenie wykresu,
plt.figure(figsize=(10, 5))
plt.plot(n_values, integral_values, marker='o', label='Metoda Prostokatow')
plt.plot(n_values, trapezoid_values, marker='x', linestyle='--', color='red', label='Metoda trapezów')
plt.plot(n_values, simpson_values, marker='x', linestyle='--', color='green', label='Metoda simpsona')
# Tytuł i etykiety osi
plt.title('Zbieżność metod całkowania')
plt.xlabel('Liczba przedziałów n')
plt.ylabel('Przybliżona wartość całki')
plt.xscale('log')  # Skala logarytmiczna, aby lepiej widzieć zmiany przy małych n
plt.legend()

# Wyświetlenie wykresu
plt.grid(True)
plt.show()