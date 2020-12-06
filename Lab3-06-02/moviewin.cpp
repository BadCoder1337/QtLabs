#include "moviewin.h"
MovieWin::MovieWin()
{
    resize(500,300);
// изменяем размеры окна так, чтобы они соответствовали размерам изображения
    slider = new QSlider(Qt::Vertical, this); // создаем "ползунок"
    slider->setRange(1,1000); // задаем интервал значений
    slider->setTickPosition(QSlider::TicksRight);
// Определяем положение насечек (рисок) на шкале ползунка
    slider->setTickInterval(50); // расстояние между делениями в условных единицах
    slider->setValue(500); // начальное значение на ползунке

 /* при изменении положения ползунка вызываем слот, который устанавливает новую задаержку: */
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setDelay(int)));
 /* Создаем стыкуемое окно (его можно пристыковать к другой границе или разместить отдельно от главного окна */
    QDockWidget* dw = new QDockWidget("Delay");
    dw->setWidget(slider); // на поверхности "стыкуемого окна" размещаем ползунок
    addDockWidget(Qt::LeftDockWidgetArea, dw);
// пристыковываем окно с ползунком к  левой границе главного окна
    label = new QLabel("Movie", this); // создаем объект label
    setCentralWidget(label); // делаем объект label рабочей областью окна
}
void MovieWin::showPix(const QPixmap *pic)
{
    label->setPixmap(*pic); // выводим очередное изображение на экран
}
void MovieWin::setDelay(int delay)
{
   QString str;
   str = QString("%1 ms").arg(delay);
   slider->setToolTip(str); /* если задержать указатель мыши на ползунке, появится надпись с текущим установленным значением */
   emit intervalChanged(delay);
// посылаем сигнал вспомогательному потоку об изменении значения
}
