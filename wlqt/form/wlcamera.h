#ifndef WLCAMERA_H
#define WLCAMERA_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class WLCamera;
}

class WLCamera : public QWidget
{
    Q_OBJECT

public:
    explicit WLCamera(QWidget *parent = nullptr);
    ~WLCamera();

private:
    Ui::WLCamera *ui;

     QScopedPointer<QCamera> m_camera;
     QScopedPointer<QCameraImageCapture> m_imageCapture;


private slots:
    void setCamera(const QCameraInfo &cameraInfo);

    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);
};

#endif // WLCAMERA_H
