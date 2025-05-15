# Función -> encontrar divisores propios de ipe
def divisores_prop(n):
    if n == 1:
        return 0
    acc = 0
    for i in range(1, n):
        if n % i == 0:
            acc += i
    return acc
    
# Función -> calcular factorial
def factorial(n):
    if n == 1 or n == 0:
        return 1
    acc = 1
    for i in range(1, n + 1):
        acc *= i
    return acc

# Uso -> calcular función corazón
def corazon(n):
    if n <= 2:
        return 0
    div_menor = 0
    divisor = 3
    while True:
        if n % divisor == 0:
            div_menor += divisor
            return div_menor
        divisor += 1
            
# Uso -> calcular función destino
def destino(n):
    exponente = 1
    denominador = 0
    termino = 0
    for i in range(1, n + 1):
        termino += (exponente ** exponente) / factorial(denominador)
        exponente += 2
        denominador += 2
    return int(termino ** 0.5)
    
# Uso -> calcular función magia
def magia(em, pr):
    elevado = em ** pr
    total = 0
    while elevado > 0:
        digito = elevado % 10
        total += digito ** 2
        elevado //= 10
    return total

# Uso -> calcular ipe en base a las 3 funciones previas
def ipe(cond1, cond2, cond3):
    return (cond1(cp) + cond2(ld)) * (cond3(em, pr))
    
# Función promoción -> determinar si existe promoción o no
def promocion(ipe):
    if (divisores_prop(ipe) > ipe) and (ipe > 0):
        return True
    return False

# Función main -> Inicializar programa
def main():
    contador = 0
    cant_ascienden = 0
    cant_no_ascienden = 0
    ipe_acc = 0
    ipe_max = 5000
    cant_ipe_max = 0
    
    while True:
        nombre = input()
        if nombre == 'FIN':
            break
        contador += 1
        
        cp = int(input())
        ld = int(input())
        em = int(input())
        pr = int(input())
        
        ipe = (corazon(cp) + destino(ld)) * (magia(em, pr))
        ipe_acc += ipe
        
        # Acumular puntajes máximos en caso de existir
        if ipe >= ipe_max:
            cant_ipe_max += 1
            
        # Imprimir
        print(f"Aspirante #{contador} : {nombre}")
        print(f"Corazón({cp}) = {corazon(cp)}")
        print(f"Destino({ld}) = {destino(ld)}")
        print(f"Magia({em},{pr}) = {magia(em,pr)}")
        print(f"Índice de Pureza Estelar = {ipe}")
        
        if promocion(ipe):
            print("*** ASPIRANTE ES PROMOVIDA AL CÍRCULO DE LA REINA ***\n")
            cant_ascienden += 1
        else:
            print()
            cant_no_ascienden += 1
    
    # Descartar y manejar casos donde no se procesan aspirantes
    if contador == 0:
        print(f"REPORTE FINAL\n============\nTotal de aspirantes procesadas = {contador}""")
        quit()
    
    else:
        ptje_ascienden = round(cant_ascienden / contador * 100, 1)
        ptje_no_ascienden = round(cant_no_ascienden / contador * 100, 1)
        ptje_max_ipe = round(cant_ipe_max / contador * 100, 1)
        
        print(f"""REPORTE FINAL
============
Total de aspirantes procesadas = {contador}
    
Promedio IPE aspirantes procesadas = {ipe_acc // contador}
{ptje_ascienden}% de las aspirantes fueron ascendidas al círculo de la reina
{ptje_max_ipe}% de las aspirantes obtuvieron un IPE mayor a 5000""")

# Inicializar función principal
main()
