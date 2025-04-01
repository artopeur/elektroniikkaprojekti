# elektroniikkaprojekti
Koulun elektroniikkaprojekti

## Projektin aikataulu
viikko 11 
- projektin aloitus hei!

viikko 12 
- projektin suunnitelma
- piirisuunnittelua

viikko 13 
- projektin
- projektin mikrokontrollerin ohjelmointia
- piirisuunnittelua, voi olla jo piirin tilaaminen
- piirin piirtämistä.

viikko 14
- suunnittelua
- projektin mikrokontrollerin ohjelmointia
- piirin tilaaminen

viikko 15
- projetin mikrokontrollerin ohjelmointia

viikko 16
- projektin mikrokontrollerin ohjelmointia

viikko 17
- projekti pitäisi olla valmis.
- Esitykset ja Posteri valmiiksi.

viikko 18 

# Datalehdet joita tarvitaan ohjelmointia varten.

Tähän lisätään datalehti linkit ja tarvittavat tiedot ohjelmointia varten.

## LCD paneeli

- LCD paneeli on mallia NHD-C0220BIZ-FSW-FBW-3V3M
- datalehti löytyy <a href = "https://newhavendisplay.com/content/specs/NHD-C0220BiZ-FSW-FBW-3V3M.pdf">tästä</a>


## Mikrokontrolleri

- Mikrokontrolleriksi valittiin AtMEGA 382BP datalehti löytyy <a href="https://ww1.microchip.com/downloads/en/DeviceDoc/40001907A.pdf">tästä</a>
- User manual löytyy <a href="https://ww1.microchip.com/downloads/en/DeviceDoc/40001906A.pdf">tästä</a>


# Arduino as programmer

- löytyy [tästä](https://app.box.com/s/ol1z8jjnrpy6wly4w61imt7wcbxk3fcg) linkistä lisätietoa.

Näyttäisi olevan melko hyvä myöskin pinnien esittämiseen. User Manuaalista pitää katsoa pinnit ohjelmointiin. Tuo löytyy siis ylempää linkistä. 

ArduinoISP löytyy ArduinoISP kansiosta. Löytyy myös esimerkeistä arduinon omasta valikoista File->Examples alta.


## Ajastimet
Ajastinten suunnittelua.

## Funktiot

- adc_init()<br>alustaa A/D- muuntimen
- timer_init()<br>alustaa ajastimen 1
- uint16_t adc_read(uint8_t channel)<br> tarkoitus lukea a/d muuntimen arvo
- float get_input_voltage()<br>muuttaa ad-muuntimen arvon jännitearvoksi
- void delay_ms(uint16_t ms)<br>käyttää Timer 3 pysäyttämään toiminnan joiksikin millisekunneiksi.
- init_timer3()<br> Alustaa timer3:n 1ms ajoitukselle 1MHz kellolla.

Timer1 - TCCR1B, OCR1A, TIMSK1 registers
: Connected to PWM signal

Timer2 - TCCR2B OCR1B, TIMSK2 registers 
: Connected to PWM2 signal

Timer3 - TCCR3B OCR3A, TIMSK3 registers
; Connected for delay function


# Viikko 13
Ohjelmointilista
- I2C määritykset, LCD I2C kirjasto? Nopeus 10kHz - 50kHz?
    - TWI moduuli?
    - (Pull up vastukset I2C väylälle?)
    - TWBR
    - Kursorin ohjaus
    - Liittimet
- PWM ohjaus taustavalolle (NMOS)
- PWM ohjaus mikrokontrollerin virtalähteelle (PMOS)
- Piirrustukset valmiiksi /?
- Tutkittavia asioita
    - Minimi virta testaus LCD paneelilla
- PINNIT
    - VDD (2.8 - 3.3 V datasheetin tietyissä kohdissa.)
    - VSS (Ground)
    - SCL (Kello)
    - SDA (Data)
    - RST (effective low) pull up resistor.
    - A anodi - pwm kontrolloitu jännite - (noin 2.8 - 3.3 v) Pulssitettuna vie vähemmän virtaa.
    - K (katodi - Ground)

Onhan tuossa nyt jo listaa. 
- Tehty delay_ms funktio, joka käyttää Timer3:sta.

# Viikko 14
 - LCD näytön ohjelmointia
    - Voidaan käyttää Timer3:n delay funktiota ajastamaan kirjoitus.
    - Piirilevy valmiiksi aikataulu maanantaina.

# Viikko 15
Lisätty koodin pätkiä.
- PWM ohjaus
- Impedanssi johtimelle
- Tilattu piirilevy

Piirilevy tilattu. Vastoinkäymisten takia KiCadin toimitetusta versiosta puuttuu pari kondensaattorin paikkaa, jotka paikataan näillä näkymin suoralla liitännällä komponentin jalkojen välille.

Pohditaan muita vaihtoehtoja.

### Ohjelmoitavaa

 - LCD Näytön koodin integroimista
 - ohjausten ja tekstin syötön tutkimista.
 - Näytön taustavalon sammutus ja sytytys.
 - RF mittaus tuloksen luku ja käsittely
 - Erillis mittaus laitteelle kytkentä tapahtuu johdoilla.
   - tämän takia tutkitaan vaihtoehtoja vieläkin, mutta toivon mukaan kytkentä toimii odotetulla tavalla.

 - Fuse bittien asetukset
 

# Viikko 16

