#define BOTTOM -1.0
#define TOP 1.0
#define LEFT -2.0
#define RIGHT 2.0
#define COLS 320
#define ROWS 160
#define ITERS 100

#define WIDTH 4.0
#define HEIGHT 2.0
#define ROW_INC (HEIGHT/ROWS)
#define COL_INC (WIDTH/COLS)

I64 getColor(F64 cr, F64 ci, F64 zr, F64 zi) {
    I64 i=0;
    F64 tzr=0.0, tzi=0.0;
    while(i<ITERS && ((zr*zr + zi*zi) < 4.0)) {
        i++;
        tzr=zr*zr-zi*zi+cr;
        tzi=2.0*zr*zi+ci;
        zr=tzr;
        zi=tzi;
    }
    return ToI64((ToF64(i)/ITERS)*15.0);
}

U0 Main() {
    "Julia Set Generator\n";
    SettingsPush;

    I64 k,j;
    CBGR48 bgr;
    for (k=0; k<16; k++) {
        j=0xFFF*k;
        bgr.b=j;
        bgr.g=j;
        bgr.r=j;
        GrPalletteColorSet(k, bgr);
    }

    CDC *dc=DCAlias;
    I64 row, col;
    for (row=0; row<ROWS; row++) {
        for (col=0; col<COLS; col++) {
            F64 r=LEFT+ToF64(COL_INC*col), i=BOTTOM+ToF64(ROW_INC*row);
            dc->color=getColor(-0.8, 0.156, r, i);
            I64 x=col*(640/COLS), y=row*(480/ROWS);
            GrRect(dc, x, y, 640/COLS, 480/ROWS);
        }
    }
    PressAKey;
    DCFill(dc);
    DCDel(dc);

    SettingsPop;
}
Main;
