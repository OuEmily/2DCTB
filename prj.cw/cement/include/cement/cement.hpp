#pragma once

#ifndef CEMENTHPP
#define CEMENTHPP

#include <iostream>
#include <vector>
#include <random>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>


namespace bg = boost::geometry;

// Определение точки и многоугольника 
typedef bg::model::point<double, 2, bg::cs::cartesian> Point;
typedef bg::model::polygon<Point> Polygon;
typedef std::vector<Polygon> Polygons;

// Класс для создания структуры цемента
/**
 * @brief Класс для генерации структуры цемента.
 * 
 * Класс предоставлят методы для создания случайной структуры цемента, визуализации 2D-модели и сочранения изображения в векторном формате SVG.
 */
class CementStructureGenerator {
public:

    /**
     * @brief Конструктор класса CementStructureGenerator.
     * 
     * @param width Ширина области генерации цемента.
     * @param height Высота области генерации цемента.
     * @param numPolygons Количество многоугольников в структуре цемента.
     * @param minPoints Минимальне количество вершин в многоугольниках.
     * @param maxPoints Максимальное количествоо вершин в многоугольниках.
     * @param rows Количество строк разделения области генерации.
     * @param cols Количество столбцов разделения области генерации.
     * @param minDistance Минимальное расстояние между многоугольниками.
     * @param extraIterations Дополнительное количество иттераций генерации.
     */
    CementStructureGenerator(double width, double height, int numPolygons, int minPoints, int maxPoints, int rows, int cols, double minDistance, int extraIterations);

    /**
     * @brief Генерация структуры цементы.
     * 
     * @return Вектор многоугольников, представляющий структуру цемента. 
     */
    Polygons generateCementStructure();

    /**
     * @brief Визуализация 2D структуры цемента.
     * 
     * @param polygons Вектор многоугольников, представляющий структуру цемента.
     * @param width Ширина изображения.
     * @param height Высота изобржения.
     */
    void visualizeModel(const Polygons& polygons, double width, double height); // Функция для визуализации 2D-модели 

    /**
     * @brief Сохранение изображения в векторном формате SVG.
     * 
     * @param polygons Вектор многоугольников, представляющий структуру цемента.
     * @param width Ширина изображения.
     * @param height Высота изобржения.
     * @param filename Имя файла для сохранения векторного изображения в формате SVG.
     */
    void saveImageAsSVG(const Polygons& polygons, double width, double height, const std::string& filename); // Функция для сохранения картинки в векторном формате (SVG)

private:
    double width; 
    double height;
    int numPolygons;
    int minPoints;
    int maxPoints;
    int rows;
    int cols;
    double minDistance;
    int extraIterations;
    Polygons polygons;

    /**
     * @brief Проверка наличия пересечений между двумя многоугольниками.
     * 
     * @param polygon1 Первый многоугольник.
     * @param polygon2 Второй многоугольник.
     * @return true, если есть пересечения
     * @return false в противном случае
     */
    bool checkIntersection(const Polygon& polygon1, const Polygon& polygon2); // Функция для проверки наличия пересечений между двумя многоугольниками

    /**
     * @brief Проверка минимального расстояния между многоугольниками.
     * 
     * @param existingPolygons Вектор уже существующих многоугольников.
     * @param newPolygon Новый многоугольник.
     * @param minDistance Минимальное расстояние.
     * @return true, если минимальное расстоения удовлетворяет условиям
     * @return false в противном случае
     */
    bool checkMinDistance(const Polygons& existingPolygons, const Polygon& newPolygon, double minDistance); // Функция для проверки минимального расстояния между многоугольниками

    /**
     * @brief Создание случайного выпуклого многоугольника в заданной области.
     * 
     * @param startX Начальная координата по оси Х.
     * @param startY Начальная координата по оси У.
     * @param endX Конечная координата по оси Х.
     * @param endY Конечная координата по оси У.
     * @param minPoints Минимальне количество вершин в многоугольнике.
     * @param maxPoints Максимальное количество вершин в многоугольнике.
     * @param sizeFactor Коэффицент варьирования размера многоугольника.
     * @return Случайный выпуклый многоугольник.
     */
    Polygon createRandomConvexPolygon(double startX, double startY, double endX, double endY, int minPoints, int maxPoints, double sizeFactor);// Функция для создания случайного многоугольника в заданной области
};
#endif