#ifndef ENTERING_SIGNIN_FORM_H
#define ENTERING_SIGNIN_FORM_H

#include <QDialog>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

namespace Ui {
class entering_signin_form;
}

class entering_signin_form : public QDialog
{
    Q_OBJECT

public:
    explicit entering_signin_form(QWidget *parent = nullptr);
    ~entering_signin_form();
    bool is_authorized() const noexcept;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::entering_signin_form *ui;
    Aws::Client::ClientConfiguration config{};
    Aws::S3::S3Client s3_client{};
    bool authorized{false};
};

#endif // ENTERING_SIGNIN_FORM_H
