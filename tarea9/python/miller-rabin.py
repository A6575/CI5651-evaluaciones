import random

def generar_numero_aleatorio(minimo, maximo):
    return random.randint(minimo, maximo)

def BTest(a, n):
    if a <= 1 or a >= n - 1:
        return False
    t = n - 1
    s = 0
    while t % 2 == 0:
        t //= 2
        s += 1
    print(f"Descomposición de n-1: n-1 = 2^{s} * {t}")
    x = pow(a, t, n)
    print(f"Cálculo inicial: x = a^t mod n = {x}")
    if x == 1 or x == n - 1:
        return True
    for _ in range(s - 1):
        x = pow(x, 2, n)
        print(f"Cálculo intermedio: x = x^2 mod n = {x}")
        if x == n - 1:
            return True
    return False

def miller_rabin(n, k=10):
    if n <= 1 or n == 4:
        return False, 0
    if n <= 3:
        return True, 0
    for i in range(k):
        a = generar_numero_aleatorio(2, n - 2)
        print(f"Iteración {i + 1}: número aleatorio a = {a}")
        if not BTest(a, n):
            return False, i + 1
    return True, 10

if __name__ == "__main__":
    numero = 181093918109391810939
    es_primo, iteraciones = miller_rabin(numero)
    if es_primo:
        print(f"{numero} es probablemente primo.")
    else:
        print(f"{numero} no es primo. Determinado en {iteraciones} iteraciones.")