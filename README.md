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
rf_adc.h
- adc_init()<br>alustaa A/D- muuntimen
- timer_init()<br>alustaa ajastimen 1 **päivitettävä**
- uint16_t adc_read(uint8_t channel)<br> tarkoitus lukea a/d muuntimen arvo
- float get_input_voltage()<br>muuttaa ad-muuntimen arvon jännitearvoksi

rf_delay_t3
- void delay_ms(uint16_t ms)<br>käyttää Timer 3 pysäyttämään toiminnan joiksikin millisekunneiksi. **päivitettävä**
- init_timer3()<br> Alustaa timer3:n 1ms ajoitukselle 1MHz kellolla. **päivitettävä**

rf_meas.h
- measurement(uint16_t, float) <br>
 Vertaa adc_read funktion arvoa jännitereferenssiin.
- reset_measurement()<br>
Tämä nollaa piikkiarvon.

rf_disp.h
- initDisp() **tekemättä**
- setText(uint8_t row, char *chars) **tekemättä**
- setbacklight(volatile uint8_t backlight) **tekemättä**

---
## Ajastimet

Timer1 - TCCR1B, OCR1A, TIMSK1 registers
: Connected to PWM signal

Timer2 - TCCR2B OCR1B, TIMSK2 registers 
: Connected to PWM2 signal : **ei käytössä** 

Timer3 - TCCR3B OCR3A, TIMSK3 registers
; Connected for delay function



# Viikkoaikataulu

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

- **AVR Programming with Arduino**: Using Arduino as ISP and setting the programmer as AVRISP mkII in Microchip Studio.<br><br>
Microchip Studio, go to "Tools" > "Device Programming", select your programmer and AVR, then set up the "Interface" and "Memories" tab for flashing.<br>

- **Bootloader**: How bootloaders are written (mostly in C/Assembly) and their role in receiving feedback and programming.

- **ATmega328PB Startup and Power**: Ensuring the chip starts reliably with fluctuating input power, using a supercapacitor, and controlling a PMOS buck converter.

- **Manual Startup Delay**: Implementing a delay in the startup using hardware (RC circuit) or software (timers) to stabilize the voltage before the chip starts functions.

- **Voltage Tolerance and Safety**: Ensuring the chip remains safe when voltage spikes (up to 5.5V) and setting the brown-out to 1.8V for proper startup.

## To read fuse settings
avrdude -c arduino -p m328pb -P COM5 -b 19200 -v

## To write low fuse (lfuse)
avrdude -c arduino -p m328pb -P COM5 -b 19200 -U lfuse:w:0xXX:m

## To write high fuse (hfuse)
avrdude -c arduino -p m328pb -P COM5 -b 19200 -U hfuse:w:0xYY:m

## To write extended fuse (efuse)
avrdude -c arduino -p m328pb -P COM5 -b 19200 -U efuse:w:0xZZ:m

## To flash a hex file to the chip
avrdude -c arduino -p m328pb -P COM5 -b 19200 -U flash:w:yourfile.hex:i

## To verify a hex file after flashing
avrdude -c arduino -p m328pb -P COM5 -b 19200 -U flash:v:yourfile.hex:i

## To erase flash before flashing
avrdude -c arduino -p m328pb -P COM5 -b 19200 -e -U flash:w:yourfile.hex:i

# Fuse bits
- **Fuse Settings**: Adjusting fuses using AVRDude, Microchip Studio, and Arduino IDE for clock and power settings (e.g., setting the clock to 1MHz, brown-out detection).

- **Brown-Out Detection**: Setting the brown-out fuse and considering voltage spikes, input power range (e.g., 2V to 5.5V).


## Brownout
avrdude -c arduino -p m328pb -P COMx -b 19200 -U efuse:w:0xFF:m -U hfuse:w:0xD9:m

Brownout and clock divide by 8, serial programming and others setup
low 0x62 = 0b 0110 0010
high 0x99 = 0b 1001 1001
extended 0xfe = 1111 1110

-U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xfe:m

Clock sources CKSEL3, CKSEL2, CKSEL0

Do we actually need CKSEL1?

Clock not divided, burnout etc.
-U lfuse:w:0xe2:m -U hfuse:w:0x99:m -U efuse:w:0xfe:m