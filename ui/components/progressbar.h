#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class progressBar;
}

class progressBar : public QDialog
{
    Q_OBJECT

public:
    explicit progressBar(QWidget *parent = nullptr);
    ~progressBar();
    int init_value = 0;
    int current_value = 0;
    bool is_closed = false;

    void setInitValue(int value);
    void setCurrentValue(int value);
private:
    Ui::progressBar *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void on_close_clicked();
};

#endif // PROGRESSBAR_H
