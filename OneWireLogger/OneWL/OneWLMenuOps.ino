//////////////////////////////////////////////////////////////////////////////
// OneWLMenuOps - Menu Operations
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// setBLt() - Set the backlight level
//////////////////////////////////////////////////////////////////////////////

void setBLt(void)
{
  signed char key;
  tft.fillScreen(ST7735_BLACK);
  textWhiteOnBlack();
  setCursorTFT(0,0);
  tft.print(F("Set Bklt"));
  setCursorTFT(1,0);
  tft.print(F("Sel=Save"));
  do
  {
    key = myOneWireLogger.pollKeypad();
    delay(100);   // allows for holding the up or down key continuously
    if ((key == DOWN) && (IZConfigs.bll <= 250))
      IZConfigs.bll += 5;
    else if ((key == UP) && (IZConfigs.bll >= 5))
      IZConfigs.bll -= 5;
    analogWrite(BACKLIGHT, IZConfigs.bll);
    setCursorTFT(0,14);
    tft.print("    ");
    setCursorTFT(0,14);
    tft.print((100*(250-IZConfigs.bll))/250);
    tft.print("%");
  }
  while (key != SELECT);
}

//////////////////////////////////////////////////////////////////////////////
// void loadConfig(void)
//////////////////////////////////////////////////////////////////////////////

void loadConfig(void)
{
  signed char key;
  tft.fillScreen(ST7735_BLACK);
  textWhiteOnBlack();
  setCursorTFT(0,0);
  tft.print(F("Sel=Load"));
  setCursorTFT(1,0);
  tft.print(F("Other=Exit"));
  while(1)
  {
    key = myOneWireLogger.waitKeyPressed();
    if (key == SELECT)
      EEPROM_readAnything(0, IZConfigs);
    if (key != NONE)
      return;
  }
}

//////////////////////////////////////////////////////////////////////////////
// void storeConfig(void)
//////////////////////////////////////////////////////////////////////////////

void storeConfig(void)
{
  signed char key;
  tft.fillScreen(ST7735_BLACK);
  textWhiteOnBlack();
  setCursorTFT(0,0);
  tft.print(F("Sel=store"));
  setCursorTFT(1,0);
  tft.print(F("Other=exit"));
  do
  {
    key = myOneWireLogger.waitKeyPressed();
    if (key == SELECT)
      EEPROM_writeAnything(0, IZConfigs);
  }
  while (key == NONE);
}

//////////////////////////////////////////////////////////////////////////////////////
// textWhiteOnBlack() - 
//////////////////////////////////////////////////////////////////////////////////////

void textWhiteOnBlack(void)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////
// setCursorTFT(int row, int col)
//////////////////////////////////////////////////////////////////////////////////////

void setCursorTFT(int row, int col)
{
  tft.setCursor(col*6, row*10);
}

