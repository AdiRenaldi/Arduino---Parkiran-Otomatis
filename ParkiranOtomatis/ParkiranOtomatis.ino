#include <Wire.h>                 //libraries untuk membaca jenis kode lcd yang dipakai
#include <LiquidCrystal_I2C.h>    //libraries untuk menjalankan i2c pada lcd
#include <Servo.h>                //libraries untuk menjalankan motor servo

LiquidCrystal_I2C lcd(0x27, 20, 4);   //menjalankan tipe lcd yang diperoleh dari libreries wire.h

Servo servo_masuk;                  //inisialisasi fungsi servo dengan parameter servo_masuk
Servo servo_keluar;                 //inisialisasi fungsi servo dengan parameter servo_keluar

// Lantai 1                         //awal infrared input
const int lantai1_1 = 2;            //inisialisasi pin 2 arduino dan ditampung didalam variabel lantai1_1
const int lantai1_2 = 3;            //inisialisasi pin 3 arduino dan ditampung didalam variabel lantai1_2

// Lantai 2
const int lantai2_1 = 4;            //inisialisasi pin 4 arduino dan ditampung didalam variabel lantai2_1
const int lantai2_2 = 5;            //inisialisasi pin 5 arduino dan ditampung didalam variabel lantai2_2

// palang pintu
const int pl_masuk = 6;             //inisialisasi pin 6 arduino dan ditampung didalam variabel pl_masuk
const int pl_keluar = 7;            //inisialisasi pin 7 arduino dan ditampung didalam variabel pl_keluar
                                    //Akhir infrared input

// Servo pin
const int masuk = 8;                //inisialisasi pin 8 arduino untuk pin output servo di tampung didalam variabel masuk
const int keluar = 9;               //inisialisasi pin 9 arduino untuk pin output servo di tampung didalam variabel keluar


void setup() {                      //fungsi untuk set variavel pin dengan aksi input dan output dan berjalan sekali di awal setiap arduino di nyalakan 
  Serial.begin(9600);               //menampilkan data ke serial monitor

  lcd.init();                       //fungsi didalam libraries untuk jalankan lcd
  lcd.backlight();                  //fungsi didalam libraries untuk menampilkan data di layar lcd

  pinMode(lantai1_1, INPUT);        //pinMode berfungsi untuk set variabel lantai1_1 sebagai inputan
  pinMode(lantai1_2, INPUT);        //pinMode berfungsi untuk set variabel lantai1_2 sebagai inputan

  pinMode(lantai2_1, INPUT);        //pinMode berfungsi untuk set variabel lantai2_1 sebagai inputan
  pinMode(lantai2_2, INPUT);        //pinMode berfungsi untuk set variabel lantai2_2 sebagai inputan

  pinMode(pl_masuk, INPUT);         //pinMode berfungsi untuk set variabel pl_masuk sebagai inputan
  pinMode(pl_keluar, INPUT);        //pinMode berfungsi untuk set variabel pl_keluar sebagai inputan

  servo_masuk.attach(masuk);        //menjalankan servo dengan output ke variabel masuk
  servo_keluar.attach(keluar);      //menjalankan servo dengan output ke variabel keluar

}

void loop() {                             //fungsi ini berjalan terus menerus berulang kali utk mengecek setiap aksi input pada sensor dan mengirim aksi output pada sensor

  // default servo
  servo_masuk.write(90);                      //mengatur nilai default servo 90 derajat pada pintu palang masuk
  servo_keluar.write(90);                     //mengatur nilai default servo 90 derajat pada pintu palang keluar

  int p_masuk = digitalRead(pl_masuk);        //menampung data inputan dari sensor infrared di variabel p_masuk
  int p_keluar = digitalRead(pl_keluar);      //menampung data inputan dari sensor infrared di variabel p_keluar

  // Lantai 1
  int inf1_1 = digitalRead(lantai1_1);        //menampung data inputan dari sensor infrared di variabel inf1_1, parkiran lantai 1 lahan 1
  int inf1_2 = digitalRead(lantai1_2);        //menampung data inputan dari sensor infrared di variabel inf1_2, parkiran lantai 1 lahan 2

  // lantai 2
  int inf2_1 = digitalRead(lantai2_1);        //menampung data inputan dari sensor infrared di variabel inf2_1, parkiran lantai 2 lahan 1
  int inf2_2 = digitalRead(lantai2_2);        //menampung data inputan dari sensor infrared di variabel inf2_2, parkiran lantai 2 lahan 2


 // palang masuk
  if(p_masuk == LOW) {                                                          //cek kondisi, jika ada objek di infrared palnag masuk, jika ada
    if(inf1_1 == HIGH || inf1_2 == HIGH || inf2_1 == HIGH || inf2_2 == HIGH){   //cek kondisi, jika semua inputan infrared HIGH berarti parkiran dalam keadaan kosong
      delay(1000);                                                              //tungg 1 detik
      servo_masuk.write(180);                                                   //buka palang pintu dengan aksi servo berpotar 180 derajat
      delay(4000);                                                              //tunggu 4 detik
      servo_masuk.write(90);                                                    //tutup palang pintu dengan aksi servo berpotar 90 derajat
    }
    else if(inf1_1 == LOW && inf1_2 == LOW && inf2_1 == LOW && inf2_2 == LOW){  //else if akan di jalankan jika kondisi diatas tidak terpenuhi, dan jika terpenuhi di kondisi ini, kondisi else if yg lainnya tdk akan di jalankan
      lcd.clear();                                                              //bersihkan layar LCD
      Serial.println("PARKIRAN MOTOR");                                         //tampilkan tulisan yg didalm kurung ke LCD
      lcd.setCursor(3, 0);
      lcd.print("PARKIRAN MOTOR");
      lcd.setCursor(5, 1);
      lcd.print("LAGI FULL");
      lcd.setCursor(1, 3);
      lcd.print("AMINA 13020190124.");

      delay(1000);
    }
  } else {
    // parkiran Full
    if (inf1_1 == LOW && inf1_2 == LOW && inf2_1 == LOW && inf2_2 == LOW) 
    {
      lcd.clear();
      Serial.println("Parkiran Full");
      lcd.setCursor(3, 0);
      lcd.print("PARKIRAN MOTOR");
      lcd.setCursor(5, 1);
      lcd.print("LAGI FULL.");
      lcd.setCursor(1, 3);
      lcd.print("AMINA 13020190124.");
      delay(1000);
    }

    // Parkiran Kosong
    else if (inf1_1 == HIGH && inf1_2 == HIGH && inf2_1 == HIGH && inf2_2 == HIGH) 
    {
      lcd.clear();
      Serial.println("Parkiran Kosong");
      lcd.setCursor(3, 0);
      lcd.print("PARKIRAN MOTOR");
      lcd.setCursor(5, 1);
      lcd.print("LAGI KOSONG!");
      lcd.setCursor(1, 3);
      lcd.print("AMINA 13020190124.");

      delay(2000);
    }

    // Lantai 1
    else if (inf1_1 == HIGH || inf1_2 == HIGH )
    {
      lcd.clear();
      Serial.println("Lantai 1 ada kosong");
      lcd.setCursor(6, 0);
      lcd.print("LANTAI 1");
      lcd.setCursor(2, 1);
      lcd.print("ADA YANG KOSONG!");
      lcd.setCursor(1, 3);
      lcd.print("AMINA 13020190124.");

      delay(1000);
    }

    // lantai 2
    else if (inf2_1 == HIGH || inf2_2 == HIGH )
    {
      lcd.clear();
      Serial.println("Lantai 2 ada kosong");
      lcd.setCursor(6, 0);
      lcd.print("LANTAI 2");
      lcd.setCursor(2, 1);
      lcd.print("ADA YANG KOSONG!");
      lcd.setCursor(1, 3);
      lcd.print("AMINA 13020190124.");

      delay(1000);
    }
  }

  // PALANG KELUAR
  if(p_keluar == LOW){      //jika ada objek di infrared palang kelaur, pintu palang akan terbuka
    delay(1000);
    servo_keluar.write(0);  //servo berputar ke 0 derajat utk membuka palang
    delay(4000);
    servo_keluar.write(90); //servo berputar ke 90 derajat utk menutup palang
    delay(1000);
  }

}
