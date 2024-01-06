# 2DCement
Приложение, осуществляющая 2D моделирование цемента.

![image](https://github.com/OuEmily/misis2023f-22-04-yuldasheva-e-d/assets/114305635/65d269d3-aa6e-4ef6-9321-b77633468457)


### На входе: 
  Параметры, вводимые пользователем: 
   
      Ширина области генерации цемента,
   
      Высота области генерации цемента,
   
      Количество многоугольников в структуре цемента,
   
      Минимальное  и максимальное количество вершин в многоугольниках,
   
      Количество строк и столбцов разделения области генерации(отвечает за то, насколько плотной будет структура, чем больше строк и столбцов, тем плотнее),
   
      Минимальное расстояние между многоугольниками, 
   
      Дополнительное количество итераций генерации (параметр отвечает за то, сколько различных размеров агрегатов встречается).

### На выходе: 
  изображение полученной модели, её векторное описание

### Функционал:

  *  моделирование структуры цемента в заданной пользователем области
  *  отрисовка полученной модели в 2D
  *  возможность получать векторное описание полученной модели
  *  возможность просматривать полученную модель

  
### Используемые библиотеки

* OprnCV (визуализация и создание геометрии)
* Boost.geometry (агрегация точек для создания многоугольников)


## Распределение задач

###### (https://github.com/OuEmily/misis2023f-22-04-yuldasheva-e-d)
Юлдашева Эмилия
  - создание геометрии модели цементно обработанного основания методом случайного агрегирования

Амирова Зарина
  - создание приложения
