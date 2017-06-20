#include "dangki.h"
#include "ui_dangki.h"

dangki::dangki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dangki)
{
    ui->setupUi(this);
    QSqlDatabase thong_tin=QSqlDatabase::addDatabase("QSQLITE");
    thong_tin.setDatabaseName("D:/tonghop2/assQTthong_tin.sqlite");
    if (!thong_tin.open())
    {
        qDebug()<<"fail";

    }
                else qDebug()<<"good";
}


dangki::~dangki()
{
    delete ui;
}
asdfh
void dangki::on_pushButton_dangki_clicked()
{
    QString hoten,tendangnhap,matkhau,xnmatkhau,xnmail,mail,CMND,sdt,ngay,thang,nam,ngaysinh,gioitinh, chucvu ,xnchucvu;
    hoten=ui->lineEdit_hoten->text();
    tendangnhap=ui->lineEdit_tendangnhap->text();
    matkhau= ui->lineEdit_matkhau->text();
    xnmatkhau=ui->lineEdit_xnmatkhau->text();
    mail=ui->lineEdit_mail->text();
    xnmail= ui->lineEdit_xnmail->text();
    CMND=ui->lineEdit_CMND->text();
    sdt= ui->lineEdit_sdt->text();
    ngay= ui->comboBox_ngay->currentText();
 thang= ui->comboBox_thang->currentText();

  nam= ui->comboBox_nam->currentText();
  ngaysinh=ngay+"/"+thang+"/"+nam;
   chucvu= ui->comboBox_chucvu->currentText();
    QSqlQuery writeQry;
     QSqlQuery qry;
         ui->label_matkhau_1->setText("");
          ui->label_xnmatkhau->setText("");
            ui->label_mail_1->setText("");
              ui->label_tendangnhap_1->setText("");
   if(ui->radioButton_nam->isChecked())
   {
           gioitinh="nam";
   }

   if(ui->radioButton_nu->isChecked())
   {
           gioitinh="nu";
   }

    if(hoten=="" || tendangnhap=="" || matkhau==""|| mail==""||CMND==""||sdt==""||xnmatkhau==""||xnmail==""||gioitinh=="")
    {

            //Kiem tra hang null
            QMessageBox::about(this,"Lỗi nhập dữ liệu!","Không được để trống dữ liệu.");
    }
    else if  (matkhau.size()<4 || matkhau.size()>12 )
    {
         ui->label_matkhau_1->setText("Mật khẩu không hợp lệ");

    }
    else if(matkhau!=xnmatkhau)
    {
        ui->label_xnmatkhau->setText("Mật khẩu xác nhận sai");

    }
    else if(mail!=xnmail)
    {
        ui->label_mail_1->setText("Mail xác nhận sai");


    }
    else if(qry.exec("select * from thongtinnguoidung where tendangnhap='"+tendangnhap +"'"))
    {
           int count=0;
           while(qry.next())
           {
               count ++;
           }
           if(count==1)  ui->label_tendangnhap_1->setText("Tên đăng nhập đã được sử dụng");
           else
           {

               writeQry.prepare("insert into thongtinnguoidung (hoten,tendangnhap,matkhau,mail,CMND,sdt,ngaysinh,gioitinh,chucvu) values"
                                " ('"+hoten+"','"+tendangnhap+"','"+matkhau+"','"+mail+"','"+CMND+"','"+sdt+"','"+ngaysinh+"','"+gioitinh+"','"+chucvu+"')");
               bool written = writeQry.exec();
               if(written)
               {
                   QMessageBox::about(this,"Thêm thành công!","Đã thêm dữ liệu vào liệu vào database.");
               }
               else
               {
                   QMessageBox::critical(this,"Lỗi!","Vui lòng kiểm tra dữ liệu nhập vào và kết nối database  ");
               }
               //Dua dong nhap ve gia tri null de cho phep nhap gia tri moi
             //  ui->lineEdit_hoten->setText("");
             //  ui->lineEdit_tendangnhap->setText("");
             //  ui->lineEdit_matkhau->setText("");
              // ui->lineEdit_mail->setText("");
              // ui->lineEdit_CMND->setText("");
             //  ui->lineEdit_sdt->setText("");
             //  ui->lineEdit_xnmatkhau->setText("");
             //  ui->lineEdit_xnmail->setText("");
             //  ui->lineEdit_machucvu->setText("");
             //  ui->label_matkhau_1->setText("");
             //  ui->label_xnmatkhau->setText("");
             //  ui->label_mail_1->setText("");
             //  ui->label_tendangnhap_1->setText("");
            }
    }
}

