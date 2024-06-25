uint8_t GetHexDigit(uint8_t hex_digit);

uint8_t *Num1ToStr(uint8_t d);
uint8_t *Num2ToStr(uint16_t d);
uint8_t *Num3ToStr(uint32_t d);
uint8_t *Num0_999ToStrSpace(uint32_t d);
uint8_t *Num0_9999ToStrSpace(uint32_t d);
uint8_t *Num0_999_m_ToStrSpace(uint32_t d);
uint8_t *Num0_999_m_ToStr_no_Space(uint32_t d);
uint8_t *Num0_9999_m_ToStrSpace(uint32_t d);
uint8_t *Num0_9999_m_ToStr_no_Space(uint32_t d);
uint8_t *Num4ToStr(uint32_t d);
uint8_t *Num5ToStr(uint32_t d);
/*
char *Num4ToStr_BlinkOneDigit(unsigned int d, unsigned char blink_digit);
*/
uint8_t *Num_uIntToStr(uint32_t d);
uint8_t *NumHexToStr(uint8_t d);
uint8_t *U32HexToStr(uint32_t d);
/*
char HexToChar (unsigned char d);
*/
//ot chislo 0-15 vrashta simvol ot 0 do F
uint8_t GetHexDigit(uint8_t hex_digit);
uint8_t CharToHex (uint8_t ch);
uint8_t CharToHex_ (uint8_t ch);
const uint8_t *OnOffString(uint8_t status);
const uint8_t *YesNo(uint8_t d);
const uint8_t *YesNo2(uint8_t d);
uint8_t CharToInt (uint8_t ch);

