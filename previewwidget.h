#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = 0);
    void drawImage(QImage* img);
    void start(int compkey, int ms); // ������������� ���� � ��������� ������� ����������

    QImage image() const;

protected:
    void paintEvent(QPaintEvent *);
    bool event(QEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

//    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    void refresh();

private slots:
    void updatePreview();

private:
    QImage* currentImage;
    int compkey; // ���� ��������� ��� preview (����� ��� ����)
    bool _resizeBegin;
};

#endif // PREVIEWWIDGET_H
