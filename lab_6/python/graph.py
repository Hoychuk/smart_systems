import numpy as np
import matplotlib.pyplot as plt

# Часові позначки
labels = ["Ранок", "День", "Вечір"]

# Матриця рівня освітленості (рядки: умови, стовпці: час)
light_levels = np.array([
    [257, 2000, 920],  # Денне світло
    [320, 515, 485],  # Штучне освітлення
    [326, 2000, 940]   # Комбіноване освітлення
])

# Назви для ліній графіка
conditions = ["Денне світло", "Штучне освітлення", "Комбіноване освітлення"]

# Побудова графіка
plt.figure(figsize=(8, 5))
for i in range(light_levels.shape[0]):
    plt.plot(labels, light_levels[i], marker='o', linestyle='-', label=conditions[i])

plt.xlabel("Час доби")
plt.ylabel("Рівень освітленості (0-1023)")
plt.title("Зміна рівня освітленості в різних умовах")
plt.legend()
plt.grid(True)
plt.show()
