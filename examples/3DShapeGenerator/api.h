
#include <fstream>

using namespace std;

/*! \file */

/// Набор возможных типов фигур
enum class ShapeType {
    Cylinder, ///< Указывает, что тип фигуры - цилиндр
    Sphere, ///< Указывает, что тип фигуры - сфера
    Plane ///< Указывает, что тип фигуры - плоскость
}; 
/*!
    \brief Структура параметров функции CreateShapes

    Структура содержит три элемента, содержащих информацию о параметрах для функции CreateShapes
    type - тип фигуры
    count - требуемое количестве сгенерированных фигур
    partition - величина стандартного отклонения для нормального распределения точек (если (= 0), нормальное распределение не используется)
*/
struct ShapeProperties {
    ShapeType type;
    int count;
    double partition;
};

/*!
    \brief Структура параметров функции CreateRandomShapes

    Структура содержит два элемента, содержащих информацию о параметрах для функции CreateShapes
    count - требуемое количестве сгенерированных фигур
    partition - величина стандартного отклонения для нормального распределения точек (если (= 0), нормальное распределение не используется)
*/
struct RandomShapeProperties {
    int count;
    double partition;
};

/*!
    Генерирует файл с именем "fileName" и расширением .csv или .json (в зависимости от того, какое расширение указано в имени),содержащий фигуры типа param.type в количестве param.count
    и величиной стандартного отклонения param.partition для нормального распределения точек
    \param fileName Имя файла
    \param param Структура параметров функции CreateShapes (смотри описание funcParams)
    \return Файл, содержащий сгенерированные данные требуемых фигур
*/
void CreateShapes(const char fileName[], ShapeProperties param);

string CreateShapes(ShapeProperties param);

/*!
    Генерирует файл с именем "fileName" и расширением .csv или .json (в зависимости от того, какое расширение указано в имени),содержащий фигуры рандомного типа в количестве param.count
    и величиной стандартного отклонения param.partition для нормального распределения точек
    \param fileName Имя файла
    \param param Структура параметров функции CreateRandomShapes (смотри описание funcParams1)
    \return Файл, содержащий сгенерированные данные требуемых фигур
*/
void CreateRandomShapes(const char fileName[], RandomShapeProperties param);

string CreateRandomShapes(RandomShapeProperties param);

