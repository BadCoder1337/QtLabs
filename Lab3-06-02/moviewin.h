#ifndef MOVIEWIN_H
#define MOVIEWIN_H
#include <QtWidgets>
class MovieWin : public QMainWindow
{
    Q_OBJECT
    QLabel* label; // элемент "надпись", используемый для вывода изображения
    QSlider* slider; // "ползунок", задающий скорость смены изображений
public:
    MovieWin();

signals:
    void intervalChanged(int newInterval);
// изменяет скорость смены изображений
public slots:
    void setDelay(int delay);
 // устанавливает задержку, которая определяет скорость смены изображений
    void showPix(const QPixmap* pix); // выводит картинку на экран
};
#endif // MOVIEWIN_H
