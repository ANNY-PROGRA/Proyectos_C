#include <stdio.h>

int main(){
    float num1, num2, resultado;
    char op;

    while (1) {
        printf("\nIngrese el primer numero: ");
        scanf("%f", &num1);

        printf("Ingrese el operador (+, -, *, /) o 'x' para salir: ");
        scanf(" %c", &op);

        if (op == 'x' || op == 'X') {
            printf("Saliendo de la calculadora...\n");
            break;
        }
        printf("Ingrese el segundo numero: ");
        scanf("%f", &num2);

        switch (op) {
            case '+':
              resultado = num1 + num2;
              break;
            case '-':
              resultado = num1 - num2;
              break;
            case '*':
              resultado = num1 * num2;
              break;
            case '/':
             if (num2 != 0) {
                resultado = num1 / num2;
             } else {
                printf("Error: Division por cero no permitida.\n");
                continue;
             } 
             break;
            default:
              printf("Operador no válido.\n");
              continue;
            }
        printf("El resultado es: %.2f\n", resultado);
    }
    
    
    return 0;
}