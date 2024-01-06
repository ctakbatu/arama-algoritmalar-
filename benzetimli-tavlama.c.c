//BENZET�ML�-TAVLAMA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// minimal hale getirmek i�in fonksiyon
double objectiveFunction(double x) {
    return x * x - 4 * x + 4;
}

// sim�le tavlama algoritmas�
double simuleTavlama() {
    double anlikDegeri = 0.0;  // anl�k degeri
    double sicaklik = 100.0;    // baslangic sicakligi
    double sogutmaHizi = 0.95;     // sogutma h�z�

    while (sicaklik > 0.01) {
        double newSolution = anlikDegeri + ((double)rand() / RAND_MAX - 0.5);  // Generate a neighboring solution

        double currentCost = objectiveFunction(anlikDegeri);
        double newCost = objectiveFunction(newSolution);

        // Metropolis criterion
        if (newCost < currentCost || ((double)rand() / RAND_MAX) < exp((currentCost - newCost) / sicaklik)) {
            anlikDegeri = newSolution;
        }

        sicaklik *= sogutmaHizi;  // Decrease temperature
    }

    return anlikDegeri;
}

int main() {
    srand(time(NULL));

    double result = simuleTavlama();

    printf("Minimum point found: %.4f\n", result);
    printf("Objective function value at minimum point: %.4f\n", objectiveFunction(result));

    return 0;
}
