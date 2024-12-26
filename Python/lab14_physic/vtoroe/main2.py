epsilon_0 = 8.85e-12  # Электрическая постоянная (Ф/м)

def calculate_condenser_parameters(U, d, epsilon_r, is_connected):
    S = 1.0
    C = epsilon_r * epsilon_0 * S / d

    if is_connected:
        Q = C * U
    else:
        Q = C * U

    E = U / d

    return E, Q, C

def main():
    U = float(input("Введите напряжение на конденсаторе (в Вольтах): "))
    d = float(input("Введите расстояние между пластинами (в метрах): "))
    epsilon_r = float(input("Введите относительную диэлектрическую проницаемость материала: "))
    is_connected = input("Конденсатор подключен к источнику питания? (да/нет): ").strip().lower() == 'да'

    E, Q, C = calculate_condenser_parameters(U, d, epsilon_r, is_connected)

    print(f"\nНачальные результаты расчета:")
    print(f"Ёмкость конденсатора: {C:.6e} Ф")
    print(f"Напряженность электрического поля: {E:.6f} Н/Кл")
    print(f"Заряд на пластинах: {Q:.20f} Кл")
    print(f"Напряжение на пластинах: {U:.6f} В")

    if input("\nИзменить параметры конденсатора? (да/нет): ").strip().lower() == 'да':
        new_d = float(input("Введите новое расстояние между пластинами (в метрах): "))
        new_epsilon_r = float(input("Введите новую относительную диэлектрическую проницаемость материала: "))

        S = 1.0
        new_C = new_epsilon_r * epsilon_0 * S / new_d

        if is_connected:
            new_Q = new_C * U  # Заряд изменяется
            new_U = U  # Напряжение остается постоянным
        else:
            new_Q = Q  # Заряд остается постоянным
            new_U = new_Q / new_C  # Напряжение изменяется

        new_E = new_U / new_d

        print(f"\nРезультаты после изменения параметров:")
        print(f"Новая ёмкость конденсатора: {new_C:.6e} Ф")
        print(f"Новая напряженность электрического поля: {new_E:.6f} Н/Кл")
        print(f"Новый заряд на пластинах: {new_Q:.20f} Кл")
        print(f"Новое напряжение на пластинах: {new_U:.6f} В")
        input("\nВведите любую клавишу для закрытия")

if __name__ == "__main__":
    main()
