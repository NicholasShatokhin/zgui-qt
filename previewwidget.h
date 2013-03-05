#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    void drawImage(QImage* img);
    void start(int compkey, int ms); // ������������� ���� � ��������� ������� ����������

protected:
    QImage* currentImage;
    int compkey; // ���� ��������� ��� preview (����� ��� ����)

    void paintEvent(QPaintEvent *);
    void refresh();

signals:
    
public slots:

private slots:
    void updatePreview();

};

#endif // PREVIEWWIDGET_H
