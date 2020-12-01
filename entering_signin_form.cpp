#include "entering_signin_form.h"
#include "ui_entering_signin_form.h"
#include <QMessageBox>

entering_signin_form::entering_signin_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::entering_signin_form)
{
    ui->setupUi(this);
}

entering_signin_form::~entering_signin_form()
{
    delete ui;
}

void entering_signin_form::on_pushButton_clicked()
{
    if(ui->lineEdit->text().length() != 0)
    {
        config.userAgent = ui->lineEdit->text().toStdString();
    }
    config.scheme = (ui->comboBox->currentText() == "HTTPS")? Aws::Http::Scheme::HTTPS : Aws::Http::Scheme::HTTP;
    config.region = ui->lineEdit_2->text().toStdString();
    if(ui->comboBox_2->currentText() != "-")
    {
        config.useDualStack = ( ui->comboBox_2->currentText() == "TRUE")? true : false;
    }
    config.maxConnections = ui->spinBox->value();
    config.requestTimeoutMs = ui->spinBox_2->value();
    config.connectTimeoutMs = ui->spinBox_3->value();
    config.endpointOverride = ui->lineEdit_3->text().toStdString();
    if(ui->lineEdit_4->text().length() != 0)
    {
        config.proxyHost = ui->lineEdit_4->text().toStdString();
        config.proxyPort = ui->lineEdit_5->text().toUInt();
        if(ui->lineEdit_6->text().length() != 0)
        {
            config.proxyUserName = ui->lineEdit_6->text().toStdString();
        }
        if(ui->lineEdit_7->text().length() != 0)
        {
            config.proxyUserName = ui->lineEdit_7->text().toStdString();
        }
    }
    config.verifySSL = (ui->comboBox_3->currentText() == "TRUE")? true : false;
    if(ui->lineEdit_8->text().length() != 0)
    {
        config.caPath = ui->lineEdit_8->text().toStdString();
    }
    Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy psp{};
    if(ui->comboBox_5->currentText() == "Request dependent")
        psp = Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::RequestDependent;
    if(ui->comboBox_5->currentText() == "Never")
        psp = Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never;
    if(ui->comboBox_5->currentText() == "Always")
        psp = Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Always;
    bool use_virtual_addressing = (ui->comboBox_6->currentText() == "TRUE")? true : false;
    s3_client = Aws::S3::S3Client(Aws::Auth::AWSCredentials(ui->lineEdit_9->text().toStdString().c_str(),
                                                            ui->lineEdit_10->text().toStdString().c_str()),
                                  config, psp,
                                  use_virtual_addressing);

    Aws::S3::Model::ListBucketsOutcome outcome = s3_client.ListBuckets();
    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        QMessageBox msgBox;
        msgBox.setInformativeText("Authentication failed.");
        msgBox.setDetailedText(err.GetMessage().c_str());
        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Retry);
        msgBox.setWindowTitle("error");
        msgBox.setIcon(QMessageBox::Critical);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Cancel)
        {
            close();
        }
    }
    else
    {
        authorized = true;
        if(outcome.GetResult().GetBuckets().empty())
        {

        }
        close();
    }
}

bool entering_signin_form::is_authorized() const noexcept
{
    return authorized;
}

void entering_signin_form::on_pushButton_2_clicked()
{
    close();
}

void entering_signin_form::on_pushButton_3_clicked()
{

}
