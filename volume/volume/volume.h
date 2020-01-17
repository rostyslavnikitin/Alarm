#ifndef VOLUME_NATIVE_LIB_H
#define VOLUME_NATIVE_LIB_H

#define DLLExport __declspec(dllexport)

extern "C"
{
	enum class VolumeUnit {
		Decibel,
		Scalar
	};

	DLLExport float GetSystemVolume(VolumeUnit);
	DLLExport void SetSystemVolume(double, VolumeUnit);
}
#endif#pragma once
