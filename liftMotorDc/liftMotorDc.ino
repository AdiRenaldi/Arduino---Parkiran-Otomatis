const int naik = 9;     //mendefinisi pin dengan menyimpan pin 9 didalam variabel naik
const int turun = 10;   //mendefinisi pin dengan menyimpan pin 10 didalam variabel turun

const int enA = 3;      //mendefinisi pin dengan menyimpan pin 3 didalam variabel enA
const int in1 = 4;
const int in2 = 5;

const int enB = 6;
const int in3 = 7;
const int in4 = 8;

void setup() {    //fungsi untuk menjalankan inisialisasi pin, berjalan sekali kecuali arduino di reset

  pinMode(naik, INPUT);     //inisialisasi pin naik sebagai inputan 
  pinMode(turun, INPUT);
  
  pinMode(enA, OUTPUT);     //menginisialisasikan enA sebagai output untuk mengatur kecepatan lift
  pinMode(enB, OUTPUT);     //menginisialisasikan enA sebagai output untuk mengatur kecepatan lift
 
  pinMode(in1, OUTPUT);     //menginisialisasikan in1 sebagai output untuk memutarkan motor dc arah kiri kada motor dc 1
  pinMode(in2, OUTPUT);     //menginisialisasikan in1 sebagai output untuk memutarkan motor dc arah kanan kada motor dc 1
  pinMode(in3, OUTPUT);     //menginisialisasikan in1 sebagai output untuk memutarkan motor dc arah kiri kada motor dc 2
  pinMode(in4, OUTPUT);     //menginisialisasikan in1 sebagai output untuk memutarkan motor dc arah kiri kada motor dc 2

  Serial.begin(9600);       //Menjalankan serial monitor pada baudrate 9600
}

void loop() {                           //fungsi ini berjalan berulang kali terus menerus selama sistem berjalan (perulangan)
  int l_naik = digitalRead(naik);       //tampung nilai inputan dari variabel naik ke variabel l_naik
  int l_turun = digitalRead(turun);     //tampung nilai inputan dari variabel turun ke variabel l_turun

  analogWrite(enA, 50);                //mengatur kecepatan motor dc 1 dengan nilai inputan 100. kecepatan inputan 0-255
  analogWrite(enB, 20);                //mengatur kecepatan motor dc 2 dengan nilai inputan 100. kecepatan inputan 0-255
  digitalWrite(in1, LOW);               //set motor dc 1 putaran kanan menjadi mati
  digitalWrite(in2, LOW);               //set motor dc 1 putaran kiri menjadi mati
  digitalWrite(in3, LOW);               //set motor dc 2 putaran kanan menjadi mati
  digitalWrite(in4, LOW);               //set motor dc 2 putaran kanan menjadi mati

  // Lift naik
  if(l_naik == LOW){                    //cek kondisi, jika inputan sensor infrared LOW artinya ada objek naik lift maka jalankan
    Serial.println("Naik");             //cetak text 'naik' di serial monitor
    analogWrite(enA, 0);                //beri output kecepatan pada enA dengan kecepatan 0 artinya tidak berjalan
    analogWrite(enB, 70);              //beri output kecepatan pada enB dengan kecepatan 100 artinya tidak berjalan
    delay(5000);                        //waktu tunggu selama 1 detik
    digitalWrite(in3, HIGH);            //jalankan motor dc 1 putar kanan, lift naik
    delay(900);                        //waktu tunggu 1 detik
    digitalWrite(in3, LOW);             //jalankan motor dc 1 putar kanan mati
    digitalWrite(in4, LOW);             //jalankan motor dc 1 putar kiri mati
    delay(5000);                        //waktu tunggu 5 detik
    digitalWrite(in4, HIGH);            //jalankan motor dc 1 putar kanan, lift turun, posisi default
    delay(500);                         //waktu tunggu kurang dari 1 detik
    digitalWrite(in3, LOW);             //jalankan motor dc 1 putar kiri mati
    digitalWrite(in4, LOW);             //jalankan motor dc 1 putar kiri mati
    delay(1000);                        //waktu tunggu selama 1 detik
  }

  // Lift turun
  if(l_turun == LOW){                   //cek kondisi, jika inputan sensor infrared LOW artinya ada objek naik lift maka jalankan
    Serial.println("turun");            //cetak text 'turun' di serial monitor
    analogWrite(enB, 0);                //beri output kecepatan pada enB dengan kecepatan 0 artinya tidak berjalan
    analogWrite(enA, 70);              //beri output kecepatan pada enA dengan kecepatan 100 artinya tidak berjalan
    delay(5000);                        //waktu tunggu selama 1 detik
    digitalWrite(in2, HIGH);            //jalankan motor dc 2 putar kiri, lift turun
    delay(1000);                        //waktu tunggu selama 1,2 detik
    digitalWrite(in1, LOW);             //jalankan motor dc 2 putar kiri mati
    digitalWrite(in2, LOW);             //jalankan motor dc 2 putar kiri mati
    delay(5000);                        //waktu tunggu selama 5 detik
    digitalWrite(in1, HIGH);            //jalankan motor dc 2 putar kiri, lift naik, posisi default
    delay(1500);                        //waktu tunggu selama 1.7 detik
    digitalWrite(in1, LOW);             //jalankan motor dc 2 putar kiri mati
    digitalWrite(in2, LOW);             //jalankan motor dc 2 putar kiri mati
    delay(1000);                        //waktu tunggu selama 1 detik
  }
  
}
