package com.epicgames.ue4;

import com.YourCompany.LifeOfMercenary.OBBDownloaderService;
import com.YourCompany.LifeOfMercenary.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

