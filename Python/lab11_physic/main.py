import numpy as np
import matplotlib.pyplot as plt

print("Введите данные для зарядов. Ограничения:")
print("  - Величина заряда (в Кл): любое число (например, 1, -1, 0.5 и т.д.)")
print("  - Координаты (x, y): значения в пределах от -5 до 5")

num_charges = int(input("Введите количество зарядов (целое число): "))
charges = []
for i in range(num_charges):
    print(f"Введите данные для заряда {i+1}:")
    q = float(input("  Величина заряда (в Кл): "))
    
    while True:
        x = float(input("  x-координата (от -5 до 5): "))
        y = float(input("  y-координата (от -5 до 5): "))
        if -5 <= x <= 5 and -5 <= y <= 5:
            break
        else:
            print("  Ошибка: координаты должны быть в пределах от -5 до 5. Повторите ввод.")
    
    charges.append({"q": q, "pos": (x, y)})

x = np.linspace(-5, 5, 500)
y = np.linspace(-5, 5, 500)
X, Y = np.meshgrid(x, y)

Ex, Ey = np.zeros_like(X), np.zeros_like(Y)
phi = np.zeros_like(X)

for charge in charges:
    q = charge["q"]
    pos = charge["pos"]
    rx = X - pos[0]
    ry = Y - pos[1]
    r = np.sqrt(rx**2 + ry**2)
    r[r == 0] = 1e-12
    Ex += q * rx / r**3
    Ey += q * ry / r**3
    phi += q / r

plt.figure(figsize=(8, 8))
plt.streamplot(X, Y, Ex, Ey, color='blue', linewidth=1, density=1.5)
contours = plt.contour(X, Y, phi, levels=20, colors='red')
plt.clabel(contours, inline=True, fontsize=8)
plt.scatter([charge["pos"][0] for charge in charges],
            [charge["pos"][1] for charge in charges],
            c='black', s=50, zorder=5)
plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.gca().set_aspect('equal')
plt.title("Линии напряженности и эквипотенциальные поверхности")
plt.show()
