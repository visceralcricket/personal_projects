# ==== MAIN ====

def mult(x, y) :
    return x * y

def div(x, y) :
    return x / y

def add(x, y) :
    return x + y

def subst(x, y) :
    return x - y

def elevar(x, y) :
    return pow(x, y)

def rest(x, y) :
    return x % y

# ==== SECONDARY ====

def val_ab(x) :
    if x < 0 :
        return x * -1
    return x

def fact(x) :
    if x <= 1 :
        return 1
    acc_val = 1
    for i in range(1, x + 1) :
        acc_val *= i
    return acc_val

# Diccionario de valores con sus respectivas funciones
operations = {
    1: add,
    2: subst,
    3: mult,
    4: div,
    5: elevar,
    6: rest,
    7: fact,
    8: val_ab
}

while True :

    # Inicializar variable que determina el cierre del programa en caso de error en valores de entrada
    validation = 0

    # Leer respuesta del usuario y entrar en ciclo hasta que el usuario decida salir
    # Utilizar funcion 'try' para crear un caso donde el valor de entrada si es valido:
    try :
        response = int(input("""Ingrese la operacion que desea realizar :
            1) Sumar
            2) Restar
            3) Multiplicar
            4) Dividir
            5) Elevar
            6) Resto
            7) Factorial
            8) Valor Absoluto
> """))
        
    except ValueError :
        print("Entrada inválida! Por favor ingrese un numero de operación válido.")
        continue    

# Verificamos si el valor NO se encuentra en el rango (1, {9 - 1})

    if response not in range(1, 9) :
        while True :
            print("Por favor, ingrese una opcion valida.")
            continue
# Preguntemos por el numero de la operacion y volvemos a testear si es valido o no

    try :

        if response in[1, 2, 3, 4, 5, 6] :
            x = int(input("Ingrese el primer valor: "))
            y = int(input("Ingrese el segundo valor: "))
            if response == 4 and y == 0 :
                print("La división con denominador 0 no es válida!")
                validation += 1
                continue
            result = operations[response](x, y)

        else :
            x = int(input("Ingrese el valor: "))
            result = operations[response](x)

    except ValueError :
        print("Entrada inválida!  Asegúrese de ingresar uno de los numeros presentados.")
        continue

    if validation == 1 :
        continue

    print(f"Resultado = {result}")
        
    leave_comm = input("Presione 0 para salir o continúe con otra operación!")
        
    if leave_comm == str(0) :
        quit()
