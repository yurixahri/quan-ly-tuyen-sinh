#ifndef CUSTOM_MESSAGE_BOX_H
#define CUSTOM_MESSAGE_BOX_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class custom_message_box;
}

class custom_message_box : public QDialog
{
    Q_OBJECT

public:
    enum MessageType {
        Information,
        Warning,
        Error,
        Question
    };

    explicit custom_message_box(const QString &title,
                              const QString &message,
                              MessageType type = Information,
                              bool askConfirm = false,
                              QWidget *parent = nullptr);

    ~custom_message_box();

private:
    Ui::custom_message_box *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CUSTOM_MESSAGE_BOX_H
