/**
 ********************************************************************************
 *@file    tft_colors_typedef.h
 * @brief   tft_colors_typedef.h Header
 * @author  Bobby 
 * @version 1
 * @date    12.12.2018
 ********************************************************************************
 */
#pragma once

#define RGB(r,g,b) (((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3))

/// @defgroup gui_colors_module TFT Color Definitions Module
/// @brief Color 565 definitions 
/// @{
typedef enum  /// TFT Color Definitions enum     
{
    
    
    ///@name Red Colors
    ///@{
    
    LIGHTSALMON             = RGB(255,160,122),     ///< <div style="background: lightsalmon"><td>&nbsp;</td> </div>
    SALMON	                = RGB(250,128,114),     ///< <div style="background: salmon"><td>&nbsp;</td> </div>
    DARKSALMON              = RGB(233,150,122),     ///< <div style="background: darksalmon"><td>&nbsp;</td> </div>
    LIGHTCORAL              = RGB(240,128,128),     ///< <div style="background: lightcoral"><td>&nbsp;</td> </div>
    INDIANRED               = RGB(205,92,92),       ///< <div style="background: indianred"><td>&nbsp;</td> </div>
    CRIMSON                 = RGB(220,20,60),       ///< <div style="background: crimson"><td>&nbsp;</td> </div>
    FIREBRICK               = RGB(178,34,34),       ///< <div style="background: firebrick"><td>&nbsp;</td> </div>
    RED                     = RGB(255,0,0),         ///< <div style="background: red"><td>&nbsp;</td> </div>
    DARKRED 	            = RGB(139,0,0),         ///< <div style="background: darkred"><td>&nbsp;</td> </div>
DARKREDV 	            = RGB(100,0,0),         ///< <div style="background: darkred"><td>&nbsp;</td> </div>
    
    ///@}
    
    
    /// @name ORANGE Colors
    /// @{
    
    CORAL                   = RGB(255,127,80),      ///< <div style="background: coral"><td>&nbsp;</td> </div>
    TOMATO 	                = RGB(255,99,71),       ///< <div style="background: tomato"><td>&nbsp;</td> </div>
    ORANGERED               = RGB(255,69,0),        ///< <div style="background: orangered"><td>&nbsp;</td> </div>
    GOLD 	                = RGB(255,215,0),       ///< <div style="background: gold"><td>&nbsp;</td> </div>
    ORANGE 	                = RGB(255,165,0),       ///< <div style="background: orange"><td>&nbsp;</td> </div>
    DARKORANGE              = RGB(255,140,0),       ///< <div style="background: darkorange"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name YELLOW Colors
    /// @{
    
    LIGHTYELLOW 	 	    = RGB(255,255,224),     ///< <div style="background: lightyellow"><td>&nbsp;</td> </div>
    LEMONCHIFFON 	 	    = RGB(255,250,205),     ///< <div style="background: lemonchiffon"><td>&nbsp;</td> </div>
    LIGHTGOLDENRODYELLOW    = RGB(250,250,210),     ///< <div style="background: lightgoldenrodyellow"><td>&nbsp;</td> </div>
    PAPAYAWHIP 	 	        = RGB(255,239,213),     ///< <div style="background: papayawhip"><td>&nbsp;</td> </div>
    MOCCASIN 	 	        = RGB(255,228,181),     ///< <div style="background: moccasin"><td>&nbsp;</td> </div>
    PEACHPUFF 	    	    = RGB(255,218,185),     ///< <div style="background: peachpuff"><td>&nbsp;</td> </div>
    PALEGOLDENROD 	 	    = RGB(238,232,170),     ///< <div style="background: palegoldenrod"><td>&nbsp;</td> </div>
    KHAKI 	                = RGB(240,230,140),     ///< <div style="background: khaki"><td>&nbsp;</td> </div>
    DARKKHAKI 	            = RGB(189,183,107),     ///< <div style="background: darkkhaki"><td>&nbsp;</td> </div>
    YELLOW 	                = RGB(255,255,0),       ///< <div style="background: yellow"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name GREEN Colors
    /// @{
    
    LAWNGREEN 	            = RGB(124,252,0),     ///< <div style="background: lawngreen"><td>&nbsp;</td> </div>
    CHARTREUSE 	            = RGB(127,255,0),     ///< <div style="background: chartreuse"><td>&nbsp;</td> </div>
    LIMEGREEN 	            = RGB(50,205,50),     ///< <div style="background: limegreen"><td>&nbsp;</td> </div>
    LIME 	                = RGB(0,255,0),       ///< <div style="background: lime"><td>&nbsp;</td> </div>
DARKLIME                        = RGB(0,210,0),
    FORESTGREEN 	        = RGB(34,139,34),     ///< <div style="background: forestgreen"><td>&nbsp;</td> </div>
    GREEN 	                = RGB(0,128,0),       ///< <div style="background: green"><td>&nbsp;</td> </div>
    DARKGREEN 	            = RGB(0,100,0),       ///< <div style="background: darkgreen"><td>&nbsp;</td> </div>
DARKGREENV 	            = RGB(0,50,0),       ///< <div style="background: darkgreen"><td>&nbsp;</td> </div>
    GREENYELLOW 	        = RGB(173,255,47),    ///< <div style="background: greenyellow"><td>&nbsp;</td> </div>
    YELLOWGREEN 	        = RGB(154,205,50),    ///< <div style="background: yellowgreen"><td>&nbsp;</td> </div>
    SPRINGGREEN 	        = RGB(0,255,127),     ///< <div style="background: springgreen"><td>&nbsp;</td> </div>
    MEDIUMSPRINGGREEN 	    = RGB(0,250,154),     ///< <div style="background: mediumspringgreen"><td>&nbsp;</td> </div>
    LIGHTGREEN 	            = RGB(144,238,144),   ///< <div style="background: lightgreen"><td>&nbsp;</td> </div>
    PALEGREEN 	            = RGB(152,251,152),   ///< <div style="background: palegreen"><td>&nbsp;</td> </div>
    DARKSEAGREEN 	        = RGB(143,188,143),   ///< <div style="background: darkseagreen"><td>&nbsp;</td> </div>
    MEDIUMSEAGREEN 	        = RGB(60,179,113),    ///< <div style="background: mediumseagreen"><td>&nbsp;</td> </div>
    SEAGREEN 	            = RGB(46,139,87),     ///< <div style="background: seagreen"><td>&nbsp;</td> </div>
    OLIVE 	                = RGB(128,128,0),     ///< <div style="background: olive"><td>&nbsp;</td> </div>
    DARKOLIVEGREEN 	        = RGB(85,107,47),     ///< <div style="background: darkolivegreen"><td>&nbsp;</td> </div>
    OLIVEDRAB 	            = RGB(107,142,35),    ///< <div style="background: olivedrab"><td>&nbsp;</td> </div>
    /// @}
    
    
    ///CYAN Colors
    /// @name CYAN Colors
    /// @{
    
    LIGHTCYAN 	            = RGB(224,255,255),     ///< <div style="background: lightcyan"><td>&nbsp;</td> </div>
    CYAN 	                = RGB(0,255,255),       ///< <div style="background: cyan"><td>&nbsp;</td> </div>
    AQUA 	                = RGB(0,255,255),       ///< <div style="background: aqua"><td>&nbsp;</td> </div>
    AQUAMARINE 	            = RGB(127,255,212),     ///< <div style="background: aquamarine"><td>&nbsp;</td> </div>
    MEDIUMAQUAMARINE 	    = RGB(102,205,170),     ///< <div style="background: mediumaquamarine"><td>&nbsp;</td> </div>
    PALETURQUOISE 	        = RGB(175,238,238),     ///< <div style="background: paleturquoise"><td>&nbsp;</td> </div>
    TURQUOISE 	            = RGB(64,224,208),      ///< <div style="background: turquoise"><td>&nbsp;</td> </div>
    MEDIUMTURQUOISE 	    = RGB(72,209,204),      ///< <div style="background: mediumturquoise"><td>&nbsp;</td> </div>
    DARKTURQUOISE 	        = RGB(0,206,209),       ///< <div style="background: darkturquoise"><td>&nbsp;</td> </div>
    LIGHTSEAGREEN 	        = RGB(32,178,170),      ///< <div style="background: lightseagreen"><td>&nbsp;</td> </div>
    CADETBLUE 	            = RGB(95,158,160),      ///< <div style="background: cadetblue"><td>&nbsp;</td> </div>
    DARKCYAN 	            = RGB(0,139,139),       ///< <div style="background: darkcyan"><td>&nbsp;</td> </div>
    TEAL 	                = RGB(0,128,128),       ///< <div style="background: teal"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name BLUE Colors
    /// @{
    
    POWDERBLUE 	    = RGB(176,224,230),			    ///< <div style="background: powderblue"><td>&nbsp;</td> </div>             
    LIGHTBLUE 	    = RGB(173,216,230),             ///< <div style="background: lightblue"><td>&nbsp;</td> </div>
    LIGHTSKYBLUE 	= RGB(135,206,250),             ///< <div style="background: lightskyblue"><td>&nbsp;</td> </div>
    SKYBLUE 	    = RGB(135,206,235),             ///< <div style="background: skyblue"><td>&nbsp;</td> </div>
    DEEPSKYBLUE 	= RGB(0,191,255),               ///< <div style="background: deepskyblue"><td>&nbsp;</td> </div>
    LIGHTSTEELBLUE 	= RGB(176,196,222),             ///< <div style="background: lightsteelblue"><td>&nbsp;</td> </div>
    DODGERBLUE 	    = RGB(30,144,255),              ///< <div style="background: dodgerblue"><td>&nbsp;</td> </div>
    CORNFLOWERBLUE 	= RGB(100,149,237),             ///< <div style="background: cornflowerblue"><td>&nbsp;</td> </div>
    STEELBLUE 	    = RGB(70,130,180),              ///< <div style="background: steelblue"><td>&nbsp;</td> </div>
    ROYALBLUE 	    = RGB(65,105,225),              ///< <div style="background: royalblue"><td>&nbsp;</td> </div>
    BLUE 	        = RGB(0,0,255),                 ///< <div style="background: blue"><td>&nbsp;</td> </div>
    MEDIUMBLUE 	    = RGB(0,0,205),                 ///< <div style="background: mediumblue"><td>&nbsp;</td> </div>
    DARKBLUE 	    = RGB(0,0,139),                 ///< <div style="background: darkblue"><td>&nbsp;</td> </div>
DARKBLUEV 	    = RGB(0,0,80),                 ///< <div style="background: darkblue"><td>&nbsp;</td> </div>
    NAVY 	        = RGB(0,0,128),                 ///< <div style="background: navy"><td>&nbsp;</td> </div>
    MIDNIGHTBLUE 	= RGB(25,25,112),               ///< <div style="background: midnightblue"><td>&nbsp;</td> </div>
    MEDIUMSLATEBLUE = RGB(123,104,238),             ///< <div style="background: mediumslateblue"><td>&nbsp;</td> </div>
    SLATEBLUE 	    = RGB(106,90,205),              ///< <div style="background: slateblue"><td>&nbsp;</td> </div>
    DARKSLATEBLUE 	= RGB(72,61,139),               ///< <div style="background: darkslateblue"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name PURPLE Colors
    /// @{
    
    LAVENDER 	    = RGB(230,230,250),             ///< <div style="background: lavender"><td>&nbsp;</td> </div> 
    THISTLE 	    = RGB(216,191,216),             ///< <div style="background: thistle"><td>&nbsp;</td> </div>
    PLUM 	        = RGB(221,160,221),             ///< <div style="background: plum"><td>&nbsp;</td> </div>
    VIOLET 	        = RGB(238,130,238),             ///< <div style="background: violet"><td>&nbsp;</td> </div>
    ORCHID 	        = RGB(218,112,214),             ///< <div style="background: orchid"><td>&nbsp;</td> </div>
    FUCHSIA 	    = RGB(255,0,255),               ///< <div style="background: fuchsia"><td>&nbsp;</td> </div>
    MAGENTA 	    = RGB(255,0,255),               ///< <div style="background: magenta"><td>&nbsp;</td> </div>
    MEDIUMORCHID 	= RGB(186,85,211),              ///< <div style="background: mediumorchid"><td>&nbsp;</td> </div>
    MEDIUMPURPLE 	= RGB(147,112,219),             ///< <div style="background: mediumpurple"><td>&nbsp;</td> </div>
    BLUEVIOLET 	    = RGB(138,43,226),              ///< <div style="background: blueviolet"><td>&nbsp;</td> </div>
    DARKVIOLET 	    = RGB(148,0,211),               ///< <div style="background: darkviolet"><td>&nbsp;</td> </div>
    DARKORCHID 	    = RGB(153,50,204),              ///< <div style="background: darkorchid"><td>&nbsp;</td> </div>
    DARKMAGENTA 	= RGB(139,0,139),               ///< <div style="background: darkmagenta"><td>&nbsp;</td> </div>
    PURPLE 	        = RGB(128,0,128),               ///< <div style="background: purple"><td>&nbsp;</td> </div>
    INDIGO 	        = RGB(75,0,130),                ///< <div style="background: indigo"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name PINK Colors
    /// @{
    
    PINK 	        = RGB(255,192,203),             ///< <div style="background: pink"><td>&nbsp;</td> </div>
    LIGHTPINK 	    = RGB(255,182,193),             ///< <div style="background: lightpink"><td>&nbsp;</td> </div>
    HOTPINK 	    = RGB(255,105,180),             ///< <div style="background: hotpink"><td>&nbsp;</td> </div>
    DEEPPINK 	    = RGB(255,20,147),              ///< <div style="background: deeppink"><td>&nbsp;</td> </div>
    PALEVIOLETRED 	= RGB(219,112,147),             ///< <div style="background: palevioletred"><td>&nbsp;</td> </div>
    MEDIUMVIOLETRED = RGB(199,21,133),              ///< <div style="background: mediumvioletred"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name WHITE Colors
    /// @{
    
    
    WHITE 	        = RGB(255,255,255),             ///< <div style="background: white"><td>&nbsp;</td> </div>
    SNOW 	        = RGB(255,250,250),             ///< <div style="background: snow"><td>&nbsp;</td> </div>
    HONEYDEW 	    = RGB(240,255,240),				///< <div style="background: honeydew"><td>&nbsp;</td> </div>
    MINTCREAM 	    = RGB(245,255,250),             ///< <div style="background: mintcream"><td>&nbsp;</td> </div>
    AZURE 	        = RGB(240,255,255),             ///< <div style="background: azure"><td>&nbsp;</td> </div>
    ALICEBLUE 	    = RGB(240,248,255),             ///< <div style="background: aliceblue"><td>&nbsp;</td> </div>
    GHOSTWHITE 	    = RGB(248,248,255),             ///< <div style="background: ghostwhite"><td>&nbsp;</td> </div>
    WHITESMOKE 	    = RGB(245,245,245),             ///< <div style="background: whitesmoke"><td>&nbsp;</td> </div>
    SEASHELL 	    = RGB(255,245,238),             ///< <div style="background: seashell"><td>&nbsp;</td> </div>
    BEIGE 	        = RGB(245,245,220),             ///< <div style="background: beige"><td>&nbsp;</td> </div>
    OLDLACE 	    = RGB(253,245,230),             ///< <div style="background: oldlace"><td>&nbsp;</td> </div>
    FLORALWHITE 	= RGB(255,250,240),             ///< <div style="background: floralwhite"><td>&nbsp;</td> </div>
    IVORY 	        = RGB(255,255,240),             ///< <div style="background: ivory"><td>&nbsp;</td> </div>
    ANTIQUEWHITE 	= RGB(250,235,215),             ///< <div style="background: antiquewhite"><td>&nbsp;</td> </div>
    LINEN 	        = RGB(250,240,230),             ///< <div style="background: linen"><td>&nbsp;</td> </div>
    LAVENDERBLUSH 	= RGB(255,240,245),             ///< <div style="background: lavenderblush"><td>&nbsp;</td> </div>
    MISTYROSE 	    = RGB(255,228,225),             ///< <div style="background: mistyrose"><td>&nbsp;</td> </div>
    /// @}
    
    
    /// @name GRAY Colors
    /// @{
    
    GAINSBORO 	    = RGB(220,220,220),			    ///< <div style="background: gainsboro"><td>&nbsp;</td> </div>
    LIGHTGRAY 	    = RGB(211,211,211),             ///< <div style="background: lightgray"><td>&nbsp;</td> </div>
    SILVER 	        = RGB(180,180,180),             ///< <div style="background: silver"><td>&nbsp;</td> </div>
SILVER_OLD 	        = RGB(192,192,192), 
    DARKGRAY 	    = RGB(169,169,169),             ///< <div style="background: darkgray"><td>&nbsp;</td> </div>
    GRAY 	        = RGB(128,128,128),             ///< <div style="background: gray"><td>&nbsp;</td> </div>
    DIMGRAY 	    = RGB(105,105,105),             ///< <div style="background: dimgray"><td>&nbsp;</td> </div>
    LIGHTSLATEGRAY 	= RGB(119,136,153),             ///< <div style="background: lightslategray"><td>&nbsp;</td> </div>
    SLATEGRAY 	    = RGB(112,128,144),             ///< <div style="background: slategray"><td>&nbsp;</td> </div>
    DARKSLATEGRAY 	= RGB(47,79,79),                ///< <div style="background: darkslategray"><td>&nbsp;</td> </div>
    BLACK 	        = RGB(0,0,0),                   ///< <div style="background: black">__________ </div>
    BLACK1 	        = RGB(8,8,8),
    /// @}
    
    
    /// @name BROWN Colors
    /// @{
    
    CORNSILK 	    = RGB(255,248,220),             ///< <div style="background: cornsilk"><td>&nbsp;</td> </div>
    BLANCHEDALMOND 	= RGB(255,235,205),             ///< <div style="background: blanchedalmond"><td>&nbsp;</td> </div>
    BISQUE 	        = RGB(255,228,196),             ///< <div style="background: bisque"><td>&nbsp;</td> </div>
    NAVAJOWHITE 	= RGB(255,222,173),             ///< <div style="background: navajowhite"><td>&nbsp;</td> </div>
    WHEAT 	        = RGB(245,222,179),             ///< <div style="background: wheat"><td>&nbsp;</td> </div>
    BURLYWOOD 	    = RGB(222,184,135),             ///< <div style="background: burlywood"><td>&nbsp;</td> </div>
    TAN 	        = RGB(210,180,140),             ///< <div style="background: tan"><td>&nbsp;</td> </div>
    ROSYBROWN 	    = RGB(188,143,143),             ///< <div style="background: rosybrown"><td>&nbsp;</td> </div>
    SANDYBROWN 	    = RGB(244,164,96),              ///< <div style="background: sandybrown"><td>&nbsp;</td> </div>
    GOLDENROD 	    = RGB(218,165,32),              ///< <div style="background: goldenrod"><td>&nbsp;</td> </div>
    PERU            = RGB(205,133,63),              ///< <div style="background: peru"><td>&nbsp;</td> </div>
    CHOCOLATE 	    = RGB(210,105,30),              ///< <div style="background: chocolate"><td>&nbsp;</td> </div>
    SADDLEBROWN 	= RGB(139,69,19),               ///< <div style="background: saddlebrown"><td>&nbsp;</td> </div>
    SIENNA 	        = RGB(160,82,45),               ///< <div style="background: sienna"><td>&nbsp;</td> </div>
    BROWN 	        = RGB(165,42,42),               ///< <div style="background: brown"><td>&nbsp;</td> </div>
    MAROON 	        = RGB(128,0,0),                 ///< <div style="background: maroon"><td>&nbsp;</td> </div>
    /// @}
}eColor_t;
/// @} End of gui_colors_module group




/* End Of File */
