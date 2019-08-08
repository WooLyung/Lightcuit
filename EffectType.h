#pragma once

enum EffectType {
	//Color
	ET_ColorMatrix				=1,
	ET_DiscreteTransfer,
	ET_GammaTransfer,
	ET_HueRotation,
	ET_LinearTransfer,
	ET_Saturation,
	ET_TableTransfer,
	//Filter
	ET_DirectionalBlur,
  //ET_EdgeDetection,			// Windows 10
	ET_GaussianBlur,
	ET_Morphology,
	//Lighting and Stylizing
  //ET_Emboss,					// Windows 10
  //ET_Posterize,				// Windows 10
	//Photo
	ET_Brightness,
  //ET_Contrast,				// Windows 10
  //ET_Exposure,				// Windows 10
  //ET_HighlightsAndShadows,	// Windows 10
  //ET_Invert,					// Windows 10
  //ET_Sepia,					// Windows 10
  //ET_Sharpen,					// Windows 10
  //ET_Vignette,				// Windows 10
	//Transform
	ET_3DTransform,
	ET_3DPerspectiveTransform,
	ET_Tile,
};