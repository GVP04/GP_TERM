#include "stdafx.h"
#include "BitmapPlus.h"
#include "GP_TermView.h"
#include "gp_term.h"


//const char *CBitmapPlus::ccA[]={"","","","",};
//const xxxx Gdiplus:: CBitmapPlus::iA[]={,,,,};


const char *CBitmapPlus::ccAEncoderParamType[]={
	"Compression",		"ColorDepth",	"ScanMethod",		"Version",
	"RenderMethod",		"Quality",		"Transformation",	"LuminanceTable",
	"ChrominanceTable",	"SaveFlag",		"ColorSpace",		"ImageItems",
	"SaveAsCMYK",		
	"EncoderCompression",		"EncoderColorDepth",	"EncoderScanMethod",		"EncoderVersion",
	"EncoderRenderMethod",		"EncoderQuality",		"EncoderTransformation",	"EncoderLuminanceTable",
	"EncoderChrominanceTable",	"EncoderSaveFlag",		"EncoderColorSpace",		"EncoderImageItems",
	"EncoderSaveAsCMYK",		
	"",				"",					"",
	};

const GUID CBitmapPlus::iAEncoderParamType[]={
	EncoderCompression,EncoderColorDepth,EncoderScanMethod,EncoderVersion,
	EncoderRenderMethod,EncoderQuality,EncoderTransformation,EncoderLuminanceTable,
	EncoderChrominanceTable,EncoderSaveFlag,EncoderColorSpace,EncoderImageItems,
	EncoderSaveAsCMYK,
	EncoderCompression,EncoderColorDepth,EncoderScanMethod,EncoderVersion,
	EncoderRenderMethod,EncoderQuality,EncoderTransformation,EncoderLuminanceTable,
	EncoderChrominanceTable,EncoderSaveFlag,EncoderColorSpace,EncoderImageItems,
	EncoderSaveAsCMYK,
	0,
};

const char *CBitmapPlus::ccAEncoderParameterValueType[]={
	"Byte","ASCII","Short","Long",
	"Rational","LongRange","Undefined","RationalRange",
	"Pointer",
	"EncoderParameterValueTypeByte","EncoderParameterValueTypeASCII","EncoderParameterValueTypeShort","EncoderParameterValueTypeLong",
	"EncoderParameterValueTypeRational","EncoderParameterValueTypeLongRange","EncoderParameterValueTypeUndefined","EncoderParameterValueTypeRationalRange",
	"Pointer",
	"","","",
	};
const EncoderParameterValueType CBitmapPlus::iAEncoderParameterValueType[]={
	EncoderParameterValueTypeByte,EncoderParameterValueTypeASCII,EncoderParameterValueTypeShort,EncoderParameterValueTypeLong,
	EncoderParameterValueTypeRational,EncoderParameterValueTypeLongRange,EncoderParameterValueTypeUndefined,EncoderParameterValueTypeRationalRange,
	EncoderParameterValueTypePointer,
	EncoderParameterValueTypeByte,EncoderParameterValueTypeASCII,EncoderParameterValueTypeShort,EncoderParameterValueTypeLong,
	EncoderParameterValueTypeRational,EncoderParameterValueTypeLongRange,EncoderParameterValueTypeUndefined,EncoderParameterValueTypeRationalRange,
	EncoderParameterValueTypePointer,
	EncoderParameterValueTypeUndefined,
	};


const char *CBitmapPlus::ccAPixelFormat[]={
	"PixelFormatIndexed","PixelFormatGDI","PixelFormatAlpha","PixelFormatPAlpha",
	"PixelFormatExtended","PixelFormatCanonical","PixelFormatUndefined","PixelFormatDontCare",
	"PixelFormat1bppIndexed","PixelFormat4bppIndexed","PixelFormat8bppIndexed","PixelFormat16bppGrayScale",
	"PixelFormat16bppRGB555","PixelFormat16bppRGB565","PixelFormat16bppARGB1555","PixelFormat24bppRGB",
	"PixelFormat32bppRGB","PixelFormat32bppARGB","PixelFormat32bppPARGB","PixelFormat48bppRGB",
	"PixelFormat64bppARGB","PixelFormat64bppPARGB","PixelFormatMax","",
};
const PixelFormat CBitmapPlus::iAPixelFormat[]={
	PixelFormatIndexed,PixelFormatGDI,PixelFormatAlpha,PixelFormatPAlpha,
	PixelFormatExtended,PixelFormatCanonical,PixelFormatUndefined,PixelFormatDontCare,
	PixelFormat1bppIndexed,PixelFormat4bppIndexed,PixelFormat8bppIndexed,PixelFormat16bppGrayScale,
	PixelFormat16bppRGB555,PixelFormat16bppRGB565,PixelFormat16bppARGB1555,PixelFormat24bppRGB,
	PixelFormat32bppRGB,PixelFormat32bppARGB,PixelFormat32bppPARGB,PixelFormat48bppRGB,
	PixelFormat64bppARGB,PixelFormat64bppPARGB,PixelFormatMax,
	PixelFormat32bppARGB,
};

const char *CBitmapPlus::ccAPaletteFlags[]={
	"HASALPHA","GRAYSCALE","HALFTONE",
	"PALETTEFLAGSHASALPHA","PALETTEFLAGSGRAYSCALE","PALETTEFLAGSHALFTONE",
	"",
};
const PaletteFlags CBitmapPlus::iAPaletteFlags[]={
	PaletteFlagsHasAlpha,PaletteFlagsGrayScale,PaletteFlagsHalftone,
	PaletteFlagsHasAlpha,PaletteFlagsGrayScale,PaletteFlagsHalftone,
	(PaletteFlags)0,
};

const char *CBitmapPlus::ccARotateFlipType[]={
	"RotateNoneFlipNone","Rotate90FlipNone","Rotate180FlipNone","Rotate270FlipNone",
	"RotateNoneFlipX","Rotate90FlipX","Rotate180FlipX","Rotate270FlipX",
	"RotateNoneFlipY","Rotate90FlipY","Rotate180FlipY","Rotate270FlipY",
	"RotateNoneFlipXY","Rotate90FlipXY","Rotate180FlipXY","Rotate270FlipXY",
	"","","","",
};
const RotateFlipType CBitmapPlus::iARotateFlipType[]={
	RotateNoneFlipNone,Rotate90FlipNone,Rotate180FlipNone,Rotate270FlipNone,
	RotateNoneFlipX,Rotate90FlipX,Rotate180FlipX,Rotate270FlipX,
	RotateNoneFlipY,Rotate90FlipY,Rotate180FlipY,Rotate270FlipY,
	RotateNoneFlipXY,Rotate90FlipXY,Rotate180FlipXY,Rotate270FlipXY,
	RotateNoneFlipNone,
};

const char *CBitmapPlus::ccAPropertyTagType[]={
	"Byte","ASCII","Short","Long",
	"Rational","Undefined","SLONG","SRational",
	"PropertyTagTypeByte","PropertyTagTypeASCII","PropertyTagTypeShort","PropertyTagTypeLong",
	"PropertyTagTypeRational","PropertyTagTypeUndefined","PropertyTagTypeSLONG","PropertyTagTypeSRational",
	"",
};
const WORD CBitmapPlus::iAPropertyTagType[]={
	PropertyTagTypeByte,PropertyTagTypeASCII,PropertyTagTypeShort,PropertyTagTypeLong,
	PropertyTagTypeRational,PropertyTagTypeUndefined,PropertyTagTypeSLONG,PropertyTagTypeSRational,
	PropertyTagTypeByte,PropertyTagTypeASCII,PropertyTagTypeShort,PropertyTagTypeLong,
	PropertyTagTypeRational,PropertyTagTypeUndefined,PropertyTagTypeSLONG,PropertyTagTypeSRational,
	PropertyTagTypeUndefined,
};

const char *CBitmapPlus::ccAUnit[]={
	"World","Display","Pixel","Point","Inch","Document","Millimeter",
	"UnitWorld","UnitDisplay","UnitPixel","UnitPoint","UnitInch","UnitDocument","UnitMillimeter",
	"",
};
const Unit CBitmapPlus::iAUnit[]={
	UnitWorld,UnitDisplay,UnitPixel,UnitPoint,UnitInch,UnitDocument,UnitMillimeter,
	UnitWorld,UnitDisplay,UnitPixel,UnitPoint,UnitInch,UnitDocument,UnitMillimeter,
	UnitWorld,
};

const char *CBitmapPlus::ccAImageFlags[]={
	"None","Scalable","HasAlpha","HasTranslucent",
	"PartiallyScalable","ColorSpaceRGB","ColorSpaceCMYK","ColorSpaceGRAY",
	"ColorSpaceYCBCR","ColorSpaceYCCK","HasRealDPI","HasRealPixelSize",
	"ReadOnly","Caching",
	"ImageFlagsNone","ImageFlagsScalable","ImageFlagsHasAlpha","ImageFlagsHasTranslucent",
	"ImageFlagsPartiallyScalable","ImageFlagsColorSpaceRGB","ImageFlagsColorSpaceCMYK","ImageFlagsColorSpaceGRAY",
	"ImageFlagsColorSpaceYCBCR","ImageFlagsColorSpaceYCCK","ImageFlagsHasRealDPI","ImageFlagsHasRealPixelSize",
	"ImageFlagsReadOnly","ImageFlagsCaching",
	"",
};

const ImageFlags CBitmapPlus::iAImageFlags[]={
	ImageFlagsNone,ImageFlagsScalable,ImageFlagsHasAlpha,ImageFlagsHasTranslucent,
	ImageFlagsPartiallyScalable,ImageFlagsColorSpaceRGB,ImageFlagsColorSpaceCMYK,ImageFlagsColorSpaceGRAY,
	ImageFlagsColorSpaceYCBCR,ImageFlagsColorSpaceYCCK,ImageFlagsHasRealDPI,ImageFlagsHasRealPixelSize,
	ImageFlagsReadOnly,ImageFlagsCaching,
	ImageFlagsNone,ImageFlagsScalable,ImageFlagsHasAlpha,ImageFlagsHasTranslucent,
	ImageFlagsPartiallyScalable,ImageFlagsColorSpaceRGB,ImageFlagsColorSpaceCMYK,ImageFlagsColorSpaceGRAY,
	ImageFlagsColorSpaceYCBCR,ImageFlagsColorSpaceYCCK,ImageFlagsHasRealDPI,ImageFlagsHasRealPixelSize,
	ImageFlagsReadOnly,ImageFlagsCaching,
	ImageFlagsNone,
};

const PROPID CBitmapPlus::iAPropertyTag[]={
	PropertyTagExifIFD	,PropertyTagGpsIFD	,PropertyTagNewSubfileType	,PropertyTagSubfileType	,PropertyTagImageWidth	,
	PropertyTagImageHeight	,PropertyTagBitsPerSample	,PropertyTagCompression	,PropertyTagPhotometricInterp	,PropertyTagThreshHolding	,
	PropertyTagCellWidth	,PropertyTagCellHeight	,PropertyTagFillOrder	,PropertyTagDocumentName	,PropertyTagImageDescription	,
	PropertyTagEquipMake	,PropertyTagEquipModel	,PropertyTagStripOffsets	,PropertyTagOrientation	,PropertyTagSamplesPerPixel	,
	PropertyTagRowsPerStrip	,PropertyTagStripBytesCount	,PropertyTagMinSampleValue	,PropertyTagMaxSampleValue	,PropertyTagXResolution	,
	PropertyTagYResolution	,PropertyTagPlanarConfig	,PropertyTagPageName	,PropertyTagXPosition	,PropertyTagYPosition	,
	PropertyTagFreeOffset	,PropertyTagFreeByteCounts	,PropertyTagGrayResponseUnit	,PropertyTagGrayResponseCurve	,PropertyTagT4Option	,
	PropertyTagT6Option	,PropertyTagResolutionUnit	,PropertyTagPageNumber	,PropertyTagTransferFuncition	,PropertyTagSoftwareUsed	,
	PropertyTagDateTime	,PropertyTagArtist	,PropertyTagHostComputer	,PropertyTagPredictor	,PropertyTagWhitePoint	,
	PropertyTagPrimaryChromaticities	,PropertyTagColorMap	,PropertyTagHalftoneHints	,PropertyTagTileWidth	,PropertyTagTileLength	,
	PropertyTagTileOffset	,PropertyTagTileByteCounts	,PropertyTagInkSet	,PropertyTagInkNames	,PropertyTagNumberOfInks	,
	PropertyTagDotRange	,PropertyTagTargetPrinter	,PropertyTagExtraSamples	,PropertyTagSampleFormat	,PropertyTagSMinSampleValue	,
	PropertyTagSMaxSampleValue	,PropertyTagTransferRange	,PropertyTagJPEGProc	,PropertyTagJPEGInterFormat	,PropertyTagJPEGInterLength	,
	PropertyTagJPEGRestartInterval	,PropertyTagJPEGLosslessPredictors	,PropertyTagJPEGPointTransforms	,PropertyTagJPEGQTables	,PropertyTagJPEGDCTables	,
	PropertyTagJPEGACTables	,PropertyTagYCbCrCoefficients	,PropertyTagYCbCrSubsampling	,PropertyTagYCbCrPositioning	,PropertyTagREFBlackWhite	,
	PropertyTagICCProfile	,PropertyTagGamma	,PropertyTagICCProfileDescriptor	,PropertyTagSRGBRenderingIntent	,PropertyTagImageTitle	,
	PropertyTagCopyright	,PropertyTagResolutionXUnit	,PropertyTagResolutionYUnit	,PropertyTagResolutionXLengthUnit	,PropertyTagResolutionYLengthUnit	,
	PropertyTagPrintFlags	,PropertyTagPrintFlagsVersion	,PropertyTagPrintFlagsCrop	,PropertyTagPrintFlagsBleedWidth	,PropertyTagPrintFlagsBleedWidthScale	,
	PropertyTagHalftoneLPI	,PropertyTagHalftoneLPIUnit	,PropertyTagHalftoneDegree	,PropertyTagHalftoneShape	,PropertyTagHalftoneMisc	,
	PropertyTagHalftoneScreen	,PropertyTagJPEGQuality	,PropertyTagGridSize	,PropertyTagThumbnailFormat	,PropertyTagThumbnailWidth	,
	PropertyTagThumbnailHeight	,PropertyTagThumbnailColorDepth	,PropertyTagThumbnailPlanes	,PropertyTagThumbnailRawBytes	,PropertyTagThumbnailSize	,
	PropertyTagThumbnailCompressedSize	,PropertyTagColorTransferFunction	,PropertyTagThumbnailData	,PropertyTagThumbnailImageWidth	,PropertyTagThumbnailImageHeight	,
	PropertyTagThumbnailBitsPerSample	,PropertyTagThumbnailCompression	,PropertyTagThumbnailPhotometricInterp	,PropertyTagThumbnailImageDescription	,PropertyTagThumbnailEquipMake	,
	PropertyTagThumbnailEquipModel	,PropertyTagThumbnailStripOffsets	,PropertyTagThumbnailOrientation	,PropertyTagThumbnailSamplesPerPixel	,PropertyTagThumbnailRowsPerStrip	,
	PropertyTagThumbnailStripBytesCount	,PropertyTagThumbnailResolutionX	,PropertyTagThumbnailResolutionY	,PropertyTagThumbnailPlanarConfig	,PropertyTagThumbnailResolutionUnit	,
	PropertyTagThumbnailTransferFunction	,PropertyTagThumbnailSoftwareUsed	,PropertyTagThumbnailDateTime	,PropertyTagThumbnailArtist	,PropertyTagThumbnailWhitePoint	,
	PropertyTagThumbnailPrimaryChromaticities	,PropertyTagThumbnailYCbCrCoefficients	,PropertyTagThumbnailYCbCrSubsampling	,PropertyTagThumbnailYCbCrPositioning	,PropertyTagThumbnailRefBlackWhite	,
	PropertyTagThumbnailCopyRight	,PropertyTagLuminanceTable	,PropertyTagChrominanceTable	,PropertyTagFrameDelay	,PropertyTagLoopCount	,
	PropertyTagGlobalPalette	,PropertyTagIndexBackground	,PropertyTagIndexTransparent	,PropertyTagPixelUnit	,PropertyTagPixelPerUnitX	,
	PropertyTagPixelPerUnitY	,PropertyTagPaletteHistogram	,PropertyTagExifExposureTime	,PropertyTagExifFNumber	,PropertyTagExifExposureProg	,
	PropertyTagExifSpectralSense	,PropertyTagExifISOSpeed	,PropertyTagExifOECF	,PropertyTagExifVer	,PropertyTagExifDTOrig	,
	PropertyTagExifDTDigitized	,PropertyTagExifCompConfig	,PropertyTagExifCompBPP	,PropertyTagExifShutterSpeed	,PropertyTagExifAperture	,
	PropertyTagExifBrightness	,PropertyTagExifExposureBias	,PropertyTagExifMaxAperture	,PropertyTagExifSubjectDist	,PropertyTagExifMeteringMode	,
	PropertyTagExifLightSource	,PropertyTagExifFlash	,PropertyTagExifFocalLength	,PropertyTagExifSubjectArea	,PropertyTagExifMakerNote	,
	PropertyTagExifUserComment	,PropertyTagExifDTSubsec	,PropertyTagExifDTOrigSS	,PropertyTagExifDTDigSS	,PropertyTagExifFPXVer	,
	PropertyTagExifColorSpace	,PropertyTagExifPixXDim	,PropertyTagExifPixYDim	,PropertyTagExifRelatedWav	,PropertyTagExifInterop	,
	PropertyTagExifFlashEnergy	,PropertyTagExifSpatialFR	,PropertyTagExifFocalXRes	,PropertyTagExifFocalYRes	,PropertyTagExifFocalResUnit	,
	PropertyTagExifSubjectLoc	,PropertyTagExifExposureIndex	,PropertyTagExifSensingMethod	,PropertyTagExifFileSource,PropertyTagExifSceneType	,
	PropertyTagExifCfaPattern	,PropertyTagExifCustomRendered	,PropertyTagExifExposureMode	,PropertyTagExifWhiteBalance	,PropertyTagExifDigitalZoomRatio	,
	PropertyTagExifFocalLengthIn35mmFilm	,PropertyTagExifSceneCaptureType	,PropertyTagExifGainControl	,PropertyTagExifContrast	,PropertyTagExifSaturation	,
	PropertyTagExifSharpness	,PropertyTagExifDeviceSettingDesc	,PropertyTagExifSubjectDistanceRange	,PropertyTagExifUniqueImageID	,PropertyTagGpsVer	,
	PropertyTagGpsLatitudeRef	,PropertyTagGpsLatitude	,PropertyTagGpsLongitudeRef	,PropertyTagGpsLongitude	,PropertyTagGpsAltitudeRef	,
	PropertyTagGpsAltitude	,PropertyTagGpsGpsTime	,PropertyTagGpsGpsSatellites	,PropertyTagGpsGpsStatus	,PropertyTagGpsGpsMeasureMode	,
	PropertyTagGpsGpsDop	,PropertyTagGpsSpeedRef	,PropertyTagGpsSpeed	,PropertyTagGpsTrackRef	,PropertyTagGpsTrack	,
	PropertyTagGpsImgDirRef	,PropertyTagGpsImgDir	,PropertyTagGpsMapDatum	,PropertyTagGpsDestLatRef	,PropertyTagGpsDestLat	,
	PropertyTagGpsDestLongRef	,PropertyTagGpsDestLong	,PropertyTagGpsDestBearRef	,PropertyTagGpsDestBear	,PropertyTagGpsDestDistRef	,
	PropertyTagGpsDestDist	,PropertyTagGpsProcessingMethod	,PropertyTagGpsAreaInformation	,PropertyTagGpsDate	,PropertyTagGpsDifferential	,
	-1,0,
};
	 


const char *CBitmapPlus::ccAPropertyTag[]={
	"ExifIFD",	"GpsIFD",	"NewSubfileType",	"SubfileType",	"ImageWidth",
	"ImageHeight",	"BitsPerSample",	"Compression",	"PhotometricInterp",	"ThreshHolding",
	"CellWidth",	"CellHeight",	"FillOrder",	"DocumentName",	"ImageDescription",
	"EquipMake",	"EquipModel",	"StripOffsets",	"Orientation",	"SamplesPerPixel",
	"RowsPerStrip",	"StripBytesCount",	"MinSampleValue",	"MaxSampleValue",	"XResolution",
	"YResolution",	"PlanarConfig",	"PageName",	"XPosition",	"YPosition",
	"FreeOffset",	"FreeByteCounts",	"GrayResponseUnit",	"GrayResponseCurve",	"T4Option",
	"T6Option",	"ResolutionUnit",	"PageNumber",	"TransferFuncition",	"SoftwareUsed",
	"DateTime",	"Artist",	"HostComputer",	"Predictor",	"WhitePoint",
	"PrimaryChromaticities",	"ColorMap",	"HalftoneHints",	"TileWidth",	"TileLength",
	"TileOffset",	"TileByteCounts",	"InkSet",	"InkNames",	"NumberOfInks",
	"DotRange",	"TargetPrinter",	"ExtraSamples",	"SampleFormat",	"SMinSampleValue",
	"SMaxSampleValue",	"TransferRange",	"JPEGProc",	"JPEGInterFormat",	"JPEGInterLength",
	"JPEGRestartInterval",	"JPEGLosslessPredictors",	"JPEGPointTransforms",	"JPEGQTables",	"JPEGDCTables",
	"JPEGACTables",	"YCbCrCoefficients",	"YCbCrSubsampling",	"YCbCrPositioning",	"REFBlackWhite",
	"ICCProfile",	"Gamma",	"ICCProfileDescriptor",	"SRGBRenderingIntent",	"ImageTitle",
	"Copyright",	"ResolutionXUnit",	"ResolutionYUnit",	"ResolutionXLengthUnit",	"ResolutionYLengthUnit",
	"PrintFlags",	"PrintFlagsVersion",	"PrintFlagsCrop",	"PrintFlagsBleedWidth",	"PrintFlagsBleedWidthScale",
	"HalftoneLPI",	"HalftoneLPIUnit",	"HalftoneDegree",	"HalftoneShape",	"HalftoneMisc",
	"HalftoneScreen",	"JPEGQuality",	"GridSize",	"ThumbnailFormat",	"ThumbnailWidth",
	"ThumbnailHeight",	"ThumbnailColorDepth",	"ThumbnailPlanes",	"ThumbnailRawBytes",	"ThumbnailSize",
	"ThumbnailCompressedSize",	"ColorTransferFunction",	"ThumbnailData",	"ThumbnailImageWidth",	"ThumbnailImageHeight",
	"ThumbnailBitsPerSample",	"ThumbnailCompression",	"ThumbnailPhotometricInterp",	"ThumbnailImageDescription",	"ThumbnailEquipMake",
	"ThumbnailEquipModel",	"ThumbnailStripOffsets",	"ThumbnailOrientation",	"ThumbnailSamplesPerPixel",	"ThumbnailRowsPerStrip",
	"ThumbnailStripBytesCount",	"ThumbnailResolutionX",	"ThumbnailResolutionY",	"ThumbnailPlanarConfig",	"ThumbnailResolutionUnit",
	"ThumbnailTransferFunction",	"ThumbnailSoftwareUsed",	"ThumbnailDateTime",	"ThumbnailArtist",	"ThumbnailWhitePoint",
	"ThumbnailPrimaryChromaticities",	"ThumbnailYCbCrCoefficients",	"ThumbnailYCbCrSubsampling",	"ThumbnailYCbCrPositioning",	"ThumbnailRefBlackWhite",
	"ThumbnailCopyRight",	"LuminanceTable",	"ChrominanceTable",	"FrameDelay",	"LoopCount",
	"GlobalPalette",	"IndexBackground",	"IndexTransparent",	"PixelUnit",	"PixelPerUnitX",
	"PixelPerUnitY",	"PaletteHistogram",	"ExifExposureTime",	"ExifFNumber",	"ExifExposureProg",
	"ExifSpectralSense",	"ExifISOSpeed",	"ExifOECF",	"ExifVer",	"ExifDTOrig",
	"ExifDTDigitized",	"ExifCompConfig",	"ExifCompBPP",	"ExifShutterSpeed",	"ExifAperture",
	"ExifBrightness",	"ExifExposureBias",	"ExifMaxAperture",	"ExifSubjectDist",	"ExifMeteringMode",
	"ExifLightSource",	"ExifFlash",	"ExifFocalLength",	"ExifSubjectArea",	"ExifMakerNote",
	"ExifUserComment",	"ExifDTSubsec",	"ExifDTOrigSS",	"ExifDTDigSS",	"ExifFPXVer",
	"ExifColorSpace",	"ExifPixXDim",	"ExifPixYDim",	"ExifRelatedWav",	"ExifInterop",
	"ExifFlashEnergy",	"ExifSpatialFR",	"ExifFocalXRes",	"ExifFocalYRes",	"ExifFocalResUnit",
	"ExifSubjectLoc",	"ExifExposureIndex",	"ExifSensingMethod",	"ExifFileSource",	"ExifSceneType",
	"ExifCfaPattern",	"ExifCustomRendered",	"ExifExposureMode",	"ExifWhiteBalance",	"ExifDigitalZoomRatio",
	"ExifFocalLengthIn35mmFilm",	"ExifSceneCaptureType",	"ExifGainControl",	"ExifContrast",	"ExifSaturation",
	"ExifSharpness",	"ExifDeviceSettingDesc",	"ExifSubjectDistanceRange",	"ExifUniqueImageID",	"GpsVer",
	"GpsLatitudeRef",	"GpsLatitude",	"GpsLongitudeRef",	"GpsLongitude",	"GpsAltitudeRef",
	"GpsAltitude",	"GpsGpsTime",	"GpsGpsSatellites",	"GpsGpsStatus",	"GpsGpsMeasureMode",
	"GpsGpsDop",	"GpsSpeedRef",	"GpsSpeed",	"GpsTrackRef",	"GpsTrack",
	"GpsImgDirRef",	"GpsImgDir",	"GpsMapDatum",	"GpsDestLatRef",	"GpsDestLat",
	"GpsDestLongRef",	"GpsDestLong",	"GpsDestBearRef",	"GpsDestBear",	"GpsDestDistRef",
	"GpsDestDist",	"GpsProcessingMethod",	"GpsAreaInformation",	"GpsDate",	"GpsDifferential",
	"",""
};

const UINT CBitmapPlus::uNMethods=43;
const char *CBitmapPlus::cArrMethods[]={
/*00*/		"GetPixel","GetPixelP","SetPixel","SetPixelP","SetPixelPC",
/*05*/		"SetResolution","GetAllPropertyItems","GetBounds","GetFlags","GetFrameCount",
/*10*/		"GetFrameDimensionsCount","GetFrameDimensionsList","GetHeight","GetHorizontalResolution","GetLastStatus",
/*15*/		"GetPalette","GetPaletteSize","GetPhysicalDimension","GetPixelFormat","GetPropertyCount",
/*20*/		"GetPropertyIdList","GetPropertyItem","GetPropertyItemSize","GetPropertySize","GetRawFormat",
/*25*/		"GetThumbnailImage","GetType","GetVerticalResolution","GetWidth","RemovePropertyItem",
/*30*/		"RotateFlip","Save","SaveAdd","SelectActiveFrame","SetPalette",
/*35*/		"SetPropertyItem","SaveP","SaveAddP","GetEncoder","SetEncoderParameter",
/*40*/		"SaveMultiFrame","SaveAddFlush","SaveThumbnails","","",
/*45*/		"","","","","",
	};
const char *CBitmapPlus::cArrMethodsParams[]={
/*00*/		"X,Y","ContextName,nPoint","X,Y,R,G,B,A","ContextName,nPoint,R,G,B,A","ContextName,nPoint,nColor",
/*05*/		"xdpi,ydpi","","srcUnit","","dimensionID",
/*10*/		"","","","","",
/*15*/		"","","","","",
/*20*/		"","propId1[,propId2[,...]]","propId","","",
/*25*/		"ContextDest,nBitmapDest,CX,CY","","","","propId1[,propId2[,...]]",
/*30*/		"rotateFlipType","FileName, Encoder/EncoderCLSID","[ContextName,nImage]","frameIndex,dimensionID","flags;R1,G1,B1,A1[;R2,G2,B2,A2...[;Rn,Gn,Bn,An]]",
/*35*/		"PropId,Type;Value1[,Value2[...]]","FileName, Encoder/EncoderCLSID","[ContextName,nImage]","Format","",
/*40*/		"FileName, Encoder/EncoderCLSID","FileName, Encoder/EncoderCLSID, CX, CY, ProgressHWND","","","",
/*45*/		"","","","","",
	};



CBitmapPlus::~CBitmapPlus(void)
{
	if (m_Bitmap) delete m_Bitmap;
	m_Bitmap=NULL;
	if (encoderParameters) delete encoderParameters;
	encoderParameters=NULL;
}

void CBitmapPlus::Init()
{
	encoderParameters=new EncoderParameters;
	encoderParameters->Count=1;
	parameterValue=0;

	ZeroMemory(&encoderParameters->Parameter[0].Guid,sizeof(GUID));
	encoderParameters->Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[0].NumberOfValues = 1;
	encoderParameters->Parameter[0].Value = &parameterValue;
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, IDirectDrawSurface7 * pIDDSurf7)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(pIDDSurf7);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, INT width,INT height,Graphics *pTarget) 
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(width, height, pTarget);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, BITMAPINFO *pgdiBitmapInfo, VOID *pgdiBitmapData)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(pgdiBitmapInfo, pgdiBitmapData);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, INT width, INT height, PixelFormat format) 
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(width, height, format);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, HBITMAP hbm, HPALETTE hpal)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(hbm, hpal);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, INT width, INT height, INT stride, PixelFormat format, BYTE *pscan0)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(width, height, stride, format, pscan0);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, WCHAR *pfilename, BOOL useIcm)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(pfilename, useIcm);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, HINSTANCE hInstance, WCHAR *pbitmapName) 
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(hInstance, pbitmapName);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, HICON hicon)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(hicon);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, IStream *pstream, BOOL useIcm)
{
	p_Context=ip_Context;
	m_Bitmap=new Bitmap(pstream, useIcm);
	Init();
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, Bitmap *p_Bitmap, BOOL bClone)
{
	p_Context=ip_Context;
	if (bClone)	m_Bitmap=p_Bitmap->Clone(0.0f, 0.0f, (REAL)p_Bitmap->GetWidth(), (REAL)p_Bitmap->GetHeight(), PixelFormatDontCare);
	else		m_Bitmap=p_Bitmap;
	Init();
}

int CBitmapPlus::GetEncoderClsid(const char* format, CLSID* pClsid)
{
	WCHAR *tmpWText=new WCHAR [strlen(format)*2+32];
	MultiByteToWideChar(CP_ACP, 0,format , -1, tmpWText,strlen(format)*2+30);
	int ret=GetEncoderClsid(tmpWText, pClsid);
	delete []tmpWText;
	return ret;
}

int CBitmapPlus::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;   
   UINT  size = 0; 
   int ret=-1;

   ImageCodecInfo* pImageCodecInfo = NULL;
   GetImageEncodersSize(&num, &size);
   if(size)
   {
	   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	   if(pImageCodecInfo)
	   {
		   GetImageEncoders(num, size, pImageCodecInfo);
		   for(UINT j = 0; j < num && ret<0; ++j)
			  if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
				 *pClsid = pImageCodecInfo[ret=j].Clsid;
		   free(pImageCodecInfo);
	   }
   }
   return ret; 
}

CBitmapPlus::CBitmapPlus(CODContext *ip_Context, DWORD dwType, const char *iStr)
{
	p_Context=ip_Context;
	m_Bitmap=NULL;

	try
	{
		if (iStr && *iStr)
			switch(dwType)
			{
			case 0: //SetBitmap  width,height,format
				{
					INT width=16,height=16;
					sscanf(iStr,"%d,%d",&width,&height);
					if (width<1 || width>100000) width=16;
					if (height<1 || height>100000) height=16;
					m_Bitmap=new Bitmap(width, height,CBitmapPlus::TranslatePixelFormat(ExtractField(iStr,3,",")));
				}
				break;
			case 1: //SetBitmapFromFile Filename,useIcm
				{
					CString fname=ExtractField(iStr,1,",");
					WCHAR *tmpWText=new WCHAR [fname.GetLength()*2+10];
					MultiByteToWideChar(CP_ACP, 0,fname , -1, tmpWText, fname.GetLength()*2);
					m_Bitmap=new Bitmap(tmpWText,atoi(ExtractField(iStr,2,",")));
					delete []tmpWText;
				}
				break;
			case 2: //SetBitmapFromIL ILname,nImage
				{
					int nImage=atoi(ExtractField(iStr,2,","));
					CString name= ExtractField(iStr,1,",");
					if (name=="") name="MISCS";
					if (nImage<0) nImage=0;

					GPImageList *SMainIl;
					int ImgLId;
					HICON m_hIcon=NULL;
					if ((ImgLId=GPC.GetImageListId(name))>=0 && (SMainIl=&(GPC.a_GPImageList[ImgLId])))
						m_hIcon=SMainIl->m_IL.ExtractIcon(nImage);
					if (m_hIcon)
					{
						m_Bitmap=new Bitmap(m_hIcon);
						::DestroyIcon(m_hIcon);
					}
				}
				break;
			case 3: //SetBitmapIndirect .....
				break; 
			case 4: //SetBitmapFromResource .....
				break;
			}
	}catch(...) {;}

	if (!m_Bitmap) m_Bitmap=new Bitmap(16,16,PixelFormat32bppARGB);
	Init();
}

PixelFormat CBitmapPlus::TranslatePixelFormat(const char *iccFormat)
{
	PixelFormat ret=PixelFormat32bppARGB;
	if (iccFormat && *iccFormat)
	{
		if (*iccFormat>='0' && *iccFormat<='9') ret=(PixelFormat)atoi(iccFormat);
		else
		{
			CString csTmp=ExtractField(iccFormat,1,",");
			int i;
			for(i=0;*CBitmapPlus::ccAPixelFormat[i] && _stricmp(csTmp,CBitmapPlus::ccAPixelFormat[i])!=0;i++);
			ret=CBitmapPlus::iAPixelFormat[i];
			if (*CBitmapPlus::ccAPixelFormat[i]==0)
			{
				CString tmpSRC(iccFormat);
				tmpSRC.MakeUpper();
				i=-1;
				do
				{
					csTmp=CBitmapPlus::ccAPixelFormat[++i];
					csTmp.MakeUpper();
				}
				while(*CBitmapPlus::ccAPixelFormat[i] && tmpSRC.Find(csTmp)<0);
				ret=CBitmapPlus::iAPixelFormat[i];
			}
		}
	}
	return ret;
}

UINT CBitmapPlus::GetPropertyDesc(const PropertyItem *pValue, char *oStr, DWORD dwLevel)
{
	UINT ret=0;
	char *posout=oStr;
	if (oStr && pValue)
	{
		BYTE delimiter1=(BYTE)((dwLevel)?1+dwLevel:0x7F);
		BYTE delimiter2=(BYTE)((dwLevel)?2+dwLevel:0x7);
		ULONG i;
		posout+=sprintf(posout,"%d%c%d%c%d%c",pValue->id,delimiter1,pValue->length,delimiter1,pValue->type,delimiter1);
		switch(pValue->type)
		{
		case PropertyTagTypeASCII:
			{
				const char *psrc=(const char *)pValue->value;
				while((*(posout++)=*(psrc++)));
			}
			break;
		case PropertyTagTypeShort:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%4.4X",((WORD*)pValue->value)[i]);
			}
			break;
		case PropertyTagTypeLong:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%8.8X",((DWORD*)pValue->value)[i]);
			}
			break;
		case PropertyTagTypeRational:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%8.8X/%8.8X",((DWORD*)pValue->value)[i*2],((DWORD*)pValue->value)[i*2+1]);
			}
			break;
		case PropertyTagTypeSLONG:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%ld",((DWORD*)pValue->value)[i]);
			}
			break;
		case PropertyTagTypeSRational:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%ld/%ld",((DWORD*)pValue->value)[i*2],((DWORD*)pValue->value)[i*2+1]);
			}
			break;
		case PropertyTagTypeUndefined:
		case PropertyTagTypeByte:
		default:
			for(i=0;i<pValue->length;i++)
			{
				if (i) {*(posout++)=delimiter2; *posout=0;}
				posout+=sprintf(posout,"%2.2X",((BYTE*)pValue->value)[i]);
			}
			break;
		}
	}
	return posout-oStr;
}

PROPID CBitmapPlus::TranslatePropertyID(const char *iccID)
{
	int i;
	for(i=0;_stricmp(iccID,CBitmapPlus::ccAPropertyTagType[i])!=0;i++);
	return CBitmapPlus::iAPropertyTagType[i];
}

UINT CBitmapPlus::DoMethod(const char *iStr, char *oStr)
{
	int nfunc=0;
	char met[150];
	strncpy(met,iStr,145);
	met[145]=0;
	const char *pos=strchr(iStr,' ');
	if (pos++) *strchr(met,' ')=0;
	else		pos="";	

	int retint=-123456; 
	int atoipos=atoi(pos);
	const char *pos2=pos;
	while(*pos2!=0 && *pos2!=',' && *pos2!='=') pos2++;
	if (*pos2!=0) pos2++;

	if (*met>='0' && *met<='9') nfunc=atoi(met);
	else
	{
		static const char *sccArrMethods[sizeof(cArrMethods)/sizeof(char *)];
		static DWORD scdMethodsId[sizeof(cArrMethods)/sizeof(char *)];
		if (!*sccArrMethods)
		{
			DWORD i;
			for(i=0;i<uNMethods;i++)
			{
				sccArrMethods[i]=cArrMethods[i];
				scdMethodsId[i]=i;
			}
			qsCharILineAndDWORD(sccArrMethods, scdMethodsId, 0, uNMethods-1);
			scdMethodsId[i]=i;
		}
		nfunc=scdMethodsId[FindInSortArrayIC(met, sccArrMethods, uNMethods)];
	}

	switch(nfunc)
	{
	case  0: //GetPixel X,Y
		if (oStr)
		{
			INT X=0,Y=0;
			Color clr(255,0,0,0);
			sscanf(pos,"%d,%d",&X,&Y);
			m_Bitmap->GetPixel(X,Y,&clr);
			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
	case  1: //GetPixelP ContextName,nPoint
		if (oStr)
		{
			Color clr(255,0,0,0);
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nObject1=atoi(ExtractField(pos,2,","));
			if (ocontext && nObject1 < ocontext->m_nPointArray)
				m_Bitmap->GetPixel((INT)ocontext->m_PointArr[nObject1].X,(INT)ocontext->m_PointArr[nObject1].Y,&clr);

			sprintf(oStr,"%d\x7F%d\x7F%d\x7F%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
		}
		break;
	case  2: //SetPixel X,Y,R,G,B,A
		{
			INT X=0,Y=0,R=0,G=0,B=0,A=255;
			sscanf(pos,"%d,%d,%d,%d,%d,%d",&X,&Y,&R,&G,&B,&A);
			m_Bitmap->SetPixel(X,Y,Color(A,R,G,B));

		}
		break;
	case  3: //SetPixelP ContextName,nPoint,R,G,B,A
	case  4: //SetPixelPC ContextName,nPoint,nColor
		{
			Color clr(255,0,0,0);
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nPoint=atoi(ExtractField(pos,2,",")),R=0;
			INT G=0,B=0,A=255;
			const char *pos2=FindField(pos,2,",");
			if (pos2 && *pos2) sscanf(pos2,"%d,%d,%d,%d,%d",&nPoint,&R,&G,&B,&A);
			if (ocontext && nPoint < ocontext->m_nPointArray)
			{
				if (nfunc==3)
					m_Bitmap->SetPixel((INT)ocontext->m_PointArr[nPoint].X,(INT)ocontext->m_PointArr[nPoint].Y,Color(A,R,G,B));
				else
					if (R>0 && R < ocontext->m_nRGBArray)
						m_Bitmap->SetPixel((INT)ocontext->m_PointArr[nPoint].X,(INT)ocontext->m_PointArr[nPoint].Y,ocontext->m_RGBArr[R]);
			}
		}
		break;
	case  5: //SetResolution xdpi,ydpi
		{
			REAL xdpi=96,ydpi=96;
			sscanf(pos,"%g,%g",&xdpi,&ydpi);
			m_Bitmap->SetResolution(xdpi,ydpi);
		}
		break;
	case  6: //GetAllPropertyItems
		if (oStr)
		{
			*oStr=0;
			UINT totalBufferSize;
			UINT numProperties;
			m_Bitmap->GetPropertySize(&totalBufferSize, &numProperties);
			if (totalBufferSize)
			{
				PropertyItem* pAllItems = (PropertyItem*)malloc(totalBufferSize);
				m_Bitmap->GetAllPropertyItems(totalBufferSize, numProperties, pAllItems);
				char *posout=oStr;
				if (pAllItems)
				{
					PropertyItem* pItem=pAllItems;

					for(UINT j = 0;  j < numProperties; ++j)
					{
						if (j) {*(posout++)=0x7F; *posout=0;}
						GetPropertyDesc(pItem++, posout, 1);
						posout+=strlen(posout);
					}
					free(pAllItems);
				}
			}
		}
		break;
	case  7: //GetBounds
		if (oStr)
		{
			RectF re(0,0,16,16);
			Unit curUnit=UnitWorld;
			m_Bitmap->GetBounds(&re,&curUnit);
			sprintf(oStr,"%d\x7F%g\x7%g\x7%g\x7%g",curUnit,re.X,re.Y,re.Width,re.Height);
		}
		break;
	case  8: //GetFlags
		retint=m_Bitmap->GetFlags();
		break;
	case  9: //GetFrameCount dimensionID
		{
			GUID gu;
			CString tmpCS(pos);
			BSTR bs=tmpCS.AllocSysString();
			CLSIDFromString(bs,&gu);
			retint=m_Bitmap->GetFrameCount(&gu);
			::SysFreeString(bs);
		}
		break;
	case 10: //GetFrameDimensionsCount
		retint=m_Bitmap->GetFrameDimensionsCount();
		break;
	case 11: //GetFrameDimensionsList 
		if (oStr)
		{
			UINT count=m_Bitmap->GetFrameDimensionsCount();
			if (count)
			{
				GUID *dimensionIDs=new GUID[count];
				m_Bitmap->GetFrameDimensionsList(dimensionIDs,count);
				GUID *pdimensionIDs=dimensionIDs;
				char *posout=oStr;
				WCHAR strGuid[50];
				while(count--)
				{
					if (posout!=oStr) {*(posout++)=0x7F; *posout=0;}
					StringFromGUID2(*(pdimensionIDs++),strGuid,48);
					posout+=sprintf(posout,"%S",strGuid);
				}
				delete []dimensionIDs;
			}
		}
		break;
	case 12: //GetHeight
		retint=m_Bitmap->GetHeight();
		break;
	case 13: //GetHorizontalResolution
		if (oStr)	sprintf(oStr,"%g",m_Bitmap->GetHorizontalResolution());
		break;
	case 14: //GetLastStatus
		retint=m_Bitmap->GetLastStatus();
		break;
	case 15: //GetPalette
		if (oStr)
		{
		    INT size=m_Bitmap->GetPaletteSize();
			if (size>0)
			{
			    ColorPalette *palette=(ColorPalette*)malloc(size);
				ZeroMemory(palette,size);
				m_Bitmap->GetPalette(palette, size);
				char *posout=oStr;
				UINT i;
				posout+=sprintf(posout,"%d\x7F%d",palette->Count,palette->Flags);
				for(i=0;i<palette->Count;i++)
				{
					Color clr(palette->Entries[i]);
					posout+=sprintf(posout,"\x7F%d\x7%d\x7%d\x7%d",clr.GetR(),clr.GetG(),clr.GetB(),clr.GetA());
				}
				free(palette);
			}
		}
		break;
	case 16: //GetPaletteSize
		retint=m_Bitmap->GetPaletteSize();
		break;
	case 17: //GetPhysicalDimension
		if (oStr)
		{
			SizeF m_size;
			m_Bitmap->GetPhysicalDimension(&m_size);
			sprintf(oStr,"%g\x7F%g",m_size.Width,m_size.Height);
		}
		break;
	case 18: //GetPixelFormat
		retint=m_Bitmap->GetPixelFormat();
		break;
	case 19: //GetPropertyCount
		retint=m_Bitmap->GetPropertyCount();
		break;
	case 20: //GetPropertyIdList
		if (oStr)
		{
			UINT numOfProperty=m_Bitmap->GetPropertyCount();
			PROPID *list=new PROPID[numOfProperty+10];
			m_Bitmap->GetPropertyIdList(numOfProperty,list);
			char *posout=oStr;
			UINT i=0;
			for(i=0;i<numOfProperty;i++)
			{
				int j;
				if (i>0) {*(posout++)=0x7F; *posout=0;}
				for(j=0;*CBitmapPlus::ccAPropertyTag[j] && CBitmapPlus::iAPropertyTag[j]!=list[i];j++);
				posout+=sprintf(posout,"%d\x7%s",list[i],CBitmapPlus::ccAPropertyTag[j]);
			}
			delete []list;
		}
		break;
	case 21: //GetPropertyItem propId1[,propId2[,...]]
		if (oStr)
		{
			char *posout=oStr;
			CString tmpCS;
			int i=0;
			while((tmpCS=ExtractField(pos,++i,","))!="")
			{
				PROPID propId=atoi(tmpCS);
				if (i>1) {*(posout++)=0x7F; *posout=0;}
				PropertyItem* propertyItem = NULL;
				UINT size = m_Bitmap->GetPropertyItemSize(propId);
				if (size>0)
				{
					propertyItem = (PropertyItem*)malloc(size);
					m_Bitmap->GetPropertyItem(propId, size, propertyItem);
					posout+=GetPropertyDesc(propertyItem, posout, 1);
					free(propertyItem);
				}
			}
		}
		break;
	case 22: //GetPropertyItemSize propId
		retint=m_Bitmap->GetPropertyItemSize(atoipos);
		break;
	case 23: //GetPropertySize
		if (oStr)
		{
			UINT totalBufferSize;
			UINT numProperties;
			m_Bitmap->GetPropertySize(&totalBufferSize, &numProperties);
			sprintf(oStr,"%d\x7F%d",totalBufferSize, numProperties);
		}
		break;
	case 24: //GetRawFormat
		if (oStr)
		{
			GUID guid;
			WCHAR strGuid[39];
			m_Bitmap->GetRawFormat(&guid);
			StringFromGUID2(guid, strGuid, 39);
			sprintf(oStr,"%S",strGuid);
		}
		break;
	case 25: //GetThumbnailImage ContextDest,nBitmapDest,CX,CY
		{
			CString ContName=ExtractField(pos,1,",");
			CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
			UINT nBitmapDest=atoi(ExtractField(pos,2,","));
			UINT thumbWidth=atoi(ExtractField(pos,3,","));
			UINT thumbHeight=atoi(ExtractField(pos,4,","));
			if (thumbWidth>=0 && thumbHeight>=0 && ocontext )
			{
				Image* pThumbnail = m_Bitmap->GetThumbnailImage(thumbWidth,thumbHeight);
				if (pThumbnail)
				{
					if ((UINT)nBitmapDest>=ocontext->m_nBitmapArray)
					{
						CBitmapPlus **tmp=new CBitmapPlus * [nBitmapDest+10];
						UINT i;
						for( i=0; i<ocontext->m_nBitmapArray;i++)		tmp[i]=ocontext->m_BitmapArr[i];
						ocontext->m_nBitmapArray=nBitmapDest+10;
						for(;i<ocontext->m_nBitmapArray;i++)	tmp[i]=NULL;
						delete[] ocontext->m_BitmapArr;
						ocontext->m_BitmapArr=tmp;
					}
					if (ocontext->m_BitmapArr[nBitmapDest]) delete ocontext->m_BitmapArr[nBitmapDest];
					ocontext->m_BitmapArr[nBitmapDest]=NULL;
					ocontext->m_BitmapArr[nBitmapDest]= new CBitmapPlus(ocontext,(Bitmap *)pThumbnail,FALSE);
				}
			}
		}
		break;
	case 26: //GetType
		retint=m_Bitmap->GetType();
		break;
	case 27: //GetVerticalResolution
		if (oStr) sprintf(oStr,"%g",m_Bitmap->GetVerticalResolution());
		break;
	case 28: //GetWidth
		retint=m_Bitmap->GetWidth();
		break;
	case 29: //RemovePropertyItem propId1[,propId2[,...]]
		{
			CString tmpCS;
			int i=0;
			while((tmpCS=ExtractField(pos,++i,","))!="")
				m_Bitmap->RemovePropertyItem(atoi(tmpCS));
		}
		break;
	case 30: //RotateFlip rotateFlipType
		{
			RotateFlipType rft=(RotateFlipType)atoipos;
			if (atoipos==0 && *pos!='0')
			{
				int i;
				for(i=0;_stricmp(pos,CBitmapPlus::ccARotateFlipType[i])!=0;i++);
				rft=CBitmapPlus::iARotateFlipType[i];
			}
			m_Bitmap->RotateFlip(rft);
		}
		break;
	case 31: //Save FileName, Encoder/EncoderCLSID
	case 36: //SaveP FileName, Encoder/EncoderCLSID
	case 40: //SaveMultiPage FileName, Encoder/EncoderCLSID
	case 42: //SaveThumbnails FileName, Encoder/EncoderCLSID, CX, CY, ProgressHWND
		{
			CLSID pngClsid;

			CString csEncoder=ExtractField(pos,2,",");
			if (csEncoder!="")
			{
				if (csEncoder.Find("{",0)<0)
				{
					GetEncoderClsid((LPCSTR)csEncoder, &pngClsid);
				}
				else
				{
					BSTR bs=csEncoder.AllocSysString();
					CLSIDFromString(bs,&pngClsid);
					::SysFreeString(bs);
				}
			}
			else pngClsid=encoderClsid;

			CString fname=ExtractField(pos,1,",");
			WCHAR *tmpWText=new WCHAR [fname.GetLength()*2+10];
			MultiByteToWideChar(CP_ACP, 0,fname , -1, tmpWText, fname.GetLength()*2);
			switch(nfunc)
			{
			case 31: //Save FileName, Encoder/EncoderCLSID
				retint=m_Bitmap->Save(tmpWText,&pngClsid,NULL);
				break;
			case 36: //SaveP FileName, Encoder/EncoderCLSID
				retint=m_Bitmap->Save(tmpWText,&pngClsid,encoderParameters);
				break;
			case 40: //SaveMultiFrame FileName, Encoder/EncoderCLSID
				{
					EncoderParameters tmp_encoderParameters;
					tmp_encoderParameters.Count=1;
					ULONG tmp_parameterValue=0;
					ZeroMemory(&tmp_encoderParameters.Parameter[0].Guid,sizeof(GUID));
					tmp_encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
					tmp_encoderParameters.Parameter[0].NumberOfValues = 1;
					tmp_encoderParameters.Parameter[0].Value = &tmp_parameterValue;
					tmp_encoderParameters.Parameter[0].Guid = EncoderSaveFlag;
					tmp_parameterValue = EncoderValueMultiFrame;
					retint=m_Bitmap->Save(tmpWText,&pngClsid,&tmp_encoderParameters);
				}
				break;
			case 42: //SaveThumbnails FileName, Encoder/EncoderCLSID, CX, CY, ProgressHWND
				{
					UINT nDims=m_Bitmap->GetFrameDimensionsCount();
					GUID *dimensionIDs=new GUID[nDims+10];
					m_Bitmap->GetFrameDimensionsList(dimensionIDs,nDims);
					GUID *pdimensionIDs=dimensionIDs;
					UINT uFrameCount=m_Bitmap->GetFrameCount(dimensionIDs);

					m_Bitmap->SelectActiveFrame(dimensionIDs,0);
					UINT CX=atoi(ExtractField(pos,3,","));
					UINT CY=atoi(ExtractField(pos,4,","));
					HWND prHWND=(HWND)atoi(ExtractField(pos,5,","));
					if (CX>10000) CX=0;
					if (CY>10000) CY=0;
					Image *tmpBmp=m_Bitmap->GetThumbnailImage(CX,CY);


					EncoderParameters tmp_encoderParameters;
					tmp_encoderParameters.Count=1;
					ULONG tmp_parameterValue=0;
					ZeroMemory(&tmp_encoderParameters.Parameter[0].Guid,sizeof(GUID));
					tmp_encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
					tmp_encoderParameters.Parameter[0].NumberOfValues = 1;
					tmp_encoderParameters.Parameter[0].Value = &tmp_parameterValue;

					tmp_encoderParameters.Parameter[0].Guid = EncoderSaveFlag;
					tmp_parameterValue = EncoderValueMultiFrame;
					tmpBmp->Save(tmpWText,&pngClsid,&tmp_encoderParameters);
					UINT i;
					if (prHWND)
					{
						::SendMessage(prHWND,PBM_SETRANGE32,0,uFrameCount);
						::SendMessage(prHWND,PBM_SETPOS,0,0);
					}
					CString tmpCS;
					for(i=1;i<uFrameCount;i++)
					{
						m_Bitmap->SelectActiveFrame(dimensionIDs,i);
						tmp_parameterValue = EncoderValueFrameDimensionPage;
						Image *tmpBmp2=m_Bitmap->GetThumbnailImage(CX,CY);
						tmpBmp->SaveAdd(tmpBmp2,&tmp_encoderParameters);
						delete tmpBmp2;
						if (prHWND)
						{
							tmpCS.Format("%d%c%d%c%d",0,3,uFrameCount,3,i);
							::SetWindowText(prHWND,tmpCS);
							::SendMessage(prHWND,PBM_SETPOS,i,0);
						}
					}

					tmp_parameterValue = EncoderValueFlush;
					tmpBmp->SaveAdd(&tmp_encoderParameters);
					
			
					delete []dimensionIDs;
					delete tmpBmp;
				}
				break;
			}
			delete []tmpWText;
		}
		break;
	case 41: //SaveAddFlush
		{
			parameterValue = EncoderValueFlush;
			m_Bitmap->SaveAdd(encoderParameters);
		}
		break;
	case 32: //SaveAdd [ContextName,nImage]
	case 37: //SaveAddP [ContextName,nImage]
		{
			Bitmap *pBitmap=NULL;
			if (*pos)
			{
				CString ContName=ExtractField(pos,1,",");
				CODContext *ocontext=(ContName=="")?p_Context:GPC.m_View->m_ODContextsArray->GetContext(ContName);
				UINT nBitmap=atoi(ExtractField(pos,2,","));
				if (nBitmap < ocontext->m_nBitmapArray && ocontext->m_BitmapArr[nBitmap] && ocontext->m_BitmapArr[nBitmap]->m_Bitmap)
				{
					if (nfunc==37)
						m_Bitmap->SaveAdd(ocontext->m_BitmapArr[nBitmap]->m_Bitmap,encoderParameters);
					else
					{
						parameterValue = EncoderValueFrameDimensionPage;
						m_Bitmap->SaveAdd(ocontext->m_BitmapArr[nBitmap]->m_Bitmap,encoderParameters);
					}
				}
			}
			else
			{
				if (nfunc!=37) 	parameterValue = EncoderValueFrameDimensionPage;
				m_Bitmap->SaveAdd(encoderParameters);
			}
		}
		break;
	case 33: //SelectActiveFrame frameIndex,dimensionID
		{
			GUID gu;
			CString tmpCS(ExtractField(pos,2,","));
			BSTR bs=tmpCS.AllocSysString();
			CLSIDFromString(bs,&gu);
			retint=m_Bitmap->GetFrameCount(&gu);
			::SysFreeString(bs);
			retint=m_Bitmap->SelectActiveFrame(&gu,atoipos);
		}
		break;
	case 34: //SetPalette flags;R1,G1,B1,A1[;R2,G2,B2,A2...[;Rn,Gn,Bn,An]]
		{
			UINT mCount=0;
			const char *pos2=pos;
			while(*pos2) if (*(pos2++)==';') mCount++;
			retint=-1;

			if (mCount)
			{
				ColorPalette* palette = (ColorPalette*)malloc(sizeof(ColorPalette) + mCount * sizeof(ARGB));
				palette->Count=mCount;
				pos2=pos;
				int i=0;
				while(pos2 && (pos2=strchr(pos2,';')))
				{
					palette->Entries[i++]=CODContext::GetColorFromString(p_Context, ++pos2);
				}
				palette->Flags=atoipos;
				CString tmpCS=ExtractField(pos,1,",");
				tmpCS.MakeUpper();
				for(i=0;*CBitmapPlus::ccAPaletteFlags[i];i++)
					if (tmpCS.Find(CBitmapPlus::ccAPaletteFlags[i],0)>=0)
						palette->Flags|=CBitmapPlus::iAPaletteFlags[i];

				retint=m_Bitmap->SetPalette(palette);
				free(palette);
			}
		}
		break;
	case 35: //SetPropertyItem PropId,Type;Value1[,Value2[...]]
		{
			PropertyItem pi;
			pi.id=(PROPID)atoipos;
			CString tmpCS=ExtractField(pos,1,",");
			int i;
			if (pi.id==0 && tmpCS[0]!='0')
			{
				for(i=0;*CBitmapPlus::ccAPropertyTag[i] && _stricmp(tmpCS,CBitmapPlus::ccAPropertyTag[i])!=0;i++);
				pi.id=-1;
				if (*CBitmapPlus::ccAPropertyTag[i]) pi.id=CBitmapPlus::iAPropertyTag[i];
			}
			else
			{
				for(i=0;*CBitmapPlus::ccAPropertyTag[i] && CBitmapPlus::iAPropertyTag[i]!=pi.id;i++);
				if (*CBitmapPlus::ccAPropertyTag[i]==0) pi.id=-1;
			}
			
			retint=-1;
			if (pi.id!=-1)
			{
				tmpCS=ExtractField(pos,2,",");
				pi.type=atoi(tmpCS);
				if (pi.type==0 && tmpCS[0]!='0')
				{
					for(i=0;*CBitmapPlus::ccAPropertyTagType[i] && _stricmp(tmpCS,CBitmapPlus::ccAPropertyTagType[i])!=0;i++);
					pi.type=-1;
					if (*CBitmapPlus::ccAPropertyTagType[i]) pi.type=CBitmapPlus::iAPropertyTagType[i];
				}
				else
				{
					for(i=0;*CBitmapPlus::ccAPropertyTagType[i] && CBitmapPlus::iAPropertyTagType[i]!=pi.type;i++);
					if (*CBitmapPlus::ccAPropertyTagType[i]==0) pi.type=-1;
				}
				const char *pos2=strchr(pos,';');
				if (pos2++ && pi.type!=-1)
				{
					pi.value= (void *) new BYTE [(strlen(pos)+16)*8];
					pi.length=0;
					switch(pi.type)
					{
					case PropertyTagTypeASCII:
						strcpy((char *)pi.value,pos2);
						pi.length=strlen(pos2)+1;
						break;
					case PropertyTagTypeShort:
						while(pos2)
						{
							long tmpv=0;
							sscanf(pos2,"%X",&tmpv);
							((short *)pi.value)[pi.length++]=(short)tmpv;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeLong:
						while(pos2)
						{
							long tmpv=0;
							sscanf(pos2,"%X",&tmpv);
							((long *)pi.value)[pi.length++]=tmpv;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeRational:
						while(pos2)
						{
							long tmpv=0,tmpv2=0;
							sscanf(pos2,"%X/%X",&tmpv,&tmpv2);
							((long *)pi.value)[pi.length*2]=tmpv;
							((long *)pi.value)[pi.length*2+1]=tmpv2;
							pi.length++;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeSLONG:
						while(pos2)
						{
							long tmpv=0;
							sscanf(pos2,"%ld",&tmpv);
							((long *)pi.value)[pi.length++]=tmpv;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeSRational:
						while(pos2)
						{
							long tmpv=0,tmpv2=0;
							sscanf(pos2,"%ld/%ld",&tmpv,&tmpv2);
							((long *)pi.value)[pi.length*2]=tmpv;
							((long *)pi.value)[pi.length*2+1]=tmpv2;
							pi.length++;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeByte:
						while(pos2)
						{
							long tmpv=0;
							sscanf(pos2,"%X",&tmpv);
							((BYTE *)pi.value)[pi.length++]=(BYTE)tmpv;
							pos2=strchr(pos2,',');
							if (pos2) pos2++;
						}
						break;
					case PropertyTagTypeUndefined:
					default:
						break;
					}
					if (pi.length) retint=m_Bitmap->SetPropertyItem(&pi);
					delete []pi.value;
				}
			}
		}
		break;
	case 38: //GetEncoder Format
		if (*pos) CBitmapPlus::GetEncoderClsid(pos, &encoderClsid);
		break;
	case 39: //SetEncoderParameter ParameterName,ParameterType;Value
		if (*pos)
		{
			const char *posvalue=FindField(pos,2,";");
			if (posvalue && *posvalue)
			{
				CString CSParamName=ExtractField(ExtractField(pos,1,";"),1,",");
				CString CSParamType=ExtractField(ExtractField(pos,1,";"),2,",");
				if (CSParamName!="" && CSParamType!="")
				{
					GUID ParamGUID;
					EncoderParameterValueType ParamType=EncoderParameterValueTypeLong;
					int i;
					for(i=0;*ccAEncoderParamType[i] && _stricmp(ccAEncoderParamType[i],CSParamName);i++);
					ParamGUID=iAEncoderParamType[i];
					for(i=0;*ccAEncoderParameterValueType[i] && _stricmp(ccAEncoderParameterValueType[i],CSParamType);i++);
					ParamType=iAEncoderParameterValueType[i];

					encoderParameters->Count = 1;
					encoderParameters->Parameter[0].Guid = ParamGUID;
					encoderParameters->Parameter[0].Type = ParamType;
					encoderParameters->Parameter[0].NumberOfValues = 1;
					encoderParameters->Parameter[0].Value = &parameterValue;

					parameterValue=atoi(posvalue);
				}
			}
		}
		break;



	default: if (oStr!=NULL)	sprintf(oStr,ErrObjSub,met);nfunc=0xFFFFFFFFL;break;
	}
	if (oStr && *oStr==0 && retint!=-123456) sprintf(oStr,"%d",retint);


	return nfunc;
}
