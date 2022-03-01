/*
 * iwinfo - Wireless Information Library - Ralink Backend
 *
 *   Copyright (C) 2016 TP-LINK Technologies Co., Ltd.
 *
 * The iwinfo library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * The iwinfo library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#include "iwinfo.h"
#include "api/wext.h"
#include "api/ra.h"


COUNTRY_CODE_TO_COUNTRY_REGION allCountry[] = {
	{8,	"AL",	"ALBANIA"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{12,	"DZ",	"ALGERIA"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{32,	"AR",	"ARGENTINA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{51,	"AM",	"ARMENIA"                     ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{533,	"AW",	"ARUBA"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{36,	"AU",	"AUSTRALIA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{40,	"AT",	"AUSTRIA"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{31,	"AZ",	"AZERBAIJAN"                  ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{44,	"BS",	"BAHAMAS"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{48,	"BH",	"BAHRAIN"                     ,	TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{50,	"BD",	"BANGLADESH"                  ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{52,	"BB",	"BARBADOS"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{112,	"BY",	"BELARUS"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{56,	"BE",	"BELGIUM"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{84,	"BZ",	"BELIZE"                      ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{60,	"BM",	"BERUMUDA"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{68,	"BO",	"BOLIVIA"                     ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{70,	"BA",	"BOSNIA AND HERZEGOVINA"      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{76,	"BR",	"BRAZIL"                      ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{96,	"BN",	"BRUNEI DARUSSALAM"           ,	TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{100,	"BG",	"BULGARIA"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{116,	"KH",	"CAMBODIA"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{124,	"CA",	"CANADA"                      ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{152,	"CL",	"CHILE"                       ,	TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{156,	"CN",	"CHINA"                       ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{170,	"CO",	"COLOMBIA"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{188,	"CR",	"COSTA RICA"                  ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{191,	"HR",	"CROATIA"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{196,	"CY",	"CYPRUS"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{203,	"CZ",	"CZECH REPUBLIC"              ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{208,	"DK",	"DENMARK"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{214,	"DO",	"DOMINICAN REPUBLIC"          ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{218,	"EC",	"ECUADOR"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{818,	"EG",	"EGYPT"                       ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{222,	"SV",	"EL SALVADOR"                 ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{233,	"EE",	"ESTONIA"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{246,	"FI",	"FINLAND"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{250,	"FR",	"FRANCE"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{268,	"GE",	"GEORGIA"                     ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{276,	"DE",	"GERMANY"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{300,	"GR",	"GREECE"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{304,	"GL",	"GREENLAND"                   ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{308,	"GD",	"GRENADA"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{316,	"GU",	"GUAM"                        ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{320,	"GT",	"GUATEMALA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{332,	"HT",	"HAITI"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{340,	"HN",	"HONDURAS"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{344,	"HK",	"HONG KONG"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{348,	"HU",	"HUNGARY"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{352,	"IS",	"ICELAND"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{356,	"IN",	"INDIA"                       ,	TRUE,	A_BAND_REGION_0,	TRUE,	G_BAND_REGION_1},
	{360,	"ID",	"INDONESIA"                   ,	TRUE,	A_BAND_REGION_5,	TRUE,	G_BAND_REGION_1},
	{364,	"IR",	"IRAN"                        ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{372,	"IE",	"IRELAND"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{376,	"IL",	"ISRAEL"                      ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{380,	"IT",	"ITALY"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{388,	"JM",	"JAMAICA"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{392,	"JP",	"JAPAN"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_5},
	{400,	"JO",	"JORDAN"                      ,	TRUE,	A_BAND_REGION_6,	TRUE,	G_BAND_REGION_1},
	{398,	"KZ",	"KAZAKHSTAN"                  ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{404,	"KE",	"KENYA"                       ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{408,	"KP",	"NORTH KOREA"                 ,	TRUE,	A_BAND_REGION_20,	TRUE,	G_BAND_REGION_1},
	{412,	"KR",	"KOREA REPUBLIC"              ,	TRUE,	A_BAND_REGION_20,	TRUE,	G_BAND_REGION_1},
	{414,	"KW",	"KUWAIT"                      ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{428,	"LV",	"LATVIA"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{422,	"LB",	"LEBANON"                     ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{438,	"LI",	"LIECHTENSTEIN"               ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{440,	"LT",	"LITHUANIA"                   ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{442,	"LU",	"LUXEMBOURG"                  ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{446,	"MO",	"MACAU SAR"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{807,	"MK",	"MACEDONIA, FYRO"             ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{458,	"MY",	"MALAYSIA"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{470,	"MT",	"MALTA"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{480,	"MU",	"MAURITIUS"                   ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{484,	"MX",	"MEXICO"                      ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{492,	"MC",	"MONACO"                      ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{504,	"MA",	"MOROCCO"                     ,	TRUE,	A_BAND_REGION_10,	TRUE,	G_BAND_REGION_1},
	{524,	"NP",	"NEPAL"                       ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{528,	"NL",	"NETHERLANDS"                 ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{554,	"NZ",	"NEW ZEALAND"                 ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{558,	"NI",	"NICARAGUA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{578,	"NO",	"NORWAY"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{512,	"OM",	"OMAN"                        ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{586,	"PK",	"PAKISTAN"                    ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{591,	"PA",	"PANAMA"                      ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{598,	"PG",	"PAPUA NEW GUINEA"            ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{600,	"PY",	"PARAGUAY"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{604,	"PE",	"PERU"                        ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{608,	"PH",	"PHILIPPINES"                 ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{616,	"PL",	"POLAND"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{620,	"PT",	"PORTUGAL"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{630,	"PR",	"PUERTO RICO"                 ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{634,	"QA",	"QATAR"                       ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{642,	"RO",	"ROMANIA"                     ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{643,	"RU",	"RUSSIA"                      ,	TRUE,	A_BAND_REGION_22,	TRUE,	G_BAND_REGION_1},
	{646,	"RW",	"RWANDA"                      ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{682,	"SA",	"SAUDI ARABIA"                ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{688,	"RS",	"REPUBLIC OF SERBIA"          ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{499,	"ME",	"MONTENEGRO"                  ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{702,	"SG",	"SINGAPORE"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{703,	"SK",	"SLOVAKIA"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{705,	"SI",	"SLOVENIA"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{710,	"ZA",	"SOUTH AFRICA"                ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{724,	"ES",	"SPAIN"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{144,	"LK",	"SRI LANKA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{752,	"SE",	"SWEDEN"                      ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{756,	"CH",	"SWITZERLAND"                 ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{760,	"SY",	"SYRIAN ARAB REPUBLIC"        ,	TRUE,	A_BAND_REGION_23,	TRUE,	G_BAND_REGION_1},
	{158,	"TW",	"TAIWAN"                      ,	TRUE,	A_BAND_REGION_23,	TRUE,	G_BAND_REGION_0},
	{834,	"TZ",	"TANZANIA"                    ,	TRUE,	A_BAND_REGION_4,	TRUE,	G_BAND_REGION_1},
	{764,	"TH",	"THAILAND"                    ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{780,	"TT",	"TRINIDAD AND TOBAGO"         ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{788,	"TN",	"TUNISIA"                     ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{792,	"TR",	"TURKEY"                      ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{800,	"UG",	"UGANDA"                      ,	TRUE,	A_BAND_REGION_21,	TRUE,	G_BAND_REGION_1},
	{804,	"UA",	"UKRAINE"                     ,	TRUE,	A_BAND_REGION_24,	TRUE,	G_BAND_REGION_1},
	{784,	"AE",	"UNITED ARAB EMIRATES"        ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{826,	"GB",	"UNITED KINGDOM"              ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{841,	"US",	"UNITED STATES"               ,	TRUE,	A_BAND_REGION_9,	TRUE,	G_BAND_REGION_0},
	{858,	"UY",	"URUGUAY"                     ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{860,	"UZ",	"UZBEKISTAN"                  ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_0},
	{862,	"VE",	"VENEZUELA"                   ,	TRUE,	A_BAND_REGION_7,	TRUE,	G_BAND_REGION_1},
	{704,	"VN",	"VIET NAM"                    ,	TRUE,	A_BAND_REGION_2,	TRUE,	G_BAND_REGION_1},
	{887,	"YE",	"YEMEN"                       ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{716,	"ZW",	"ZIMBABWE"                    ,	TRUE,	A_BAND_REGION_1,	TRUE,	G_BAND_REGION_1},
	{999,	"",	"",	0,	0,	0,	0}
};

static double ra_freq2float(const struct iw_freq *in)
{
	int		i;
	double	res = (double) in->m;
	for(i = 0; i < in->e; i++) res *= 10;
	return res;
}

static inline int ra_freq2mhz(const struct iw_freq *in)
{
	if( in->e == 6 )
	{
		return in->m;
	}
	else
	{
		return (int)(ra_freq2float(in) / 1000000);
	}
}

static int ra_ioctl(const char *name, int cmd, void *buf, int len)
{
	struct ifreq ifr;

	strncpy(ifr.ifr_name, name, IFNAMSIZ);
	ifr.ifr_data = NULL;

	return iwinfo_ioctl(SIOCDEVPRIVATE, &ifr);
}

static int ra_probe(const char *ifname)
{
	return wext_ops.probe(ifname);
}

static void ra_close(void)
{
	/* Nop */
}

static int ra_get_mode(const char *ifname, int *buf)
{
	return wext_ops.mode(ifname, buf);
}

static int ra_get_ssid(const char *ifname, char *buf)
{
	return wext_ops.ssid(ifname, buf);
}

static int ra_get_bssid(const char *ifname, char *buf)
{
	return wext_ops.bssid(ifname, buf);
}

static int ra_get_channel(const char *ifname, int *buf)
{
	return wext_ops.channel(ifname, buf);
}

static int ra_get_frequency(const char *ifname, int *buf)
{
	return wext_ops.frequency(ifname, buf);
}

static int ra_get_txpower(const char *ifname, int *buf)
{
	return wext_ops.txpower(ifname, buf);
}

static int ra_get_bitrate(const char *ifname, int *buf)
{
    return wext_ops.bitrate(ifname, buf);
}

static int ra_get_signal(const char *ifname, int *buf)
{
    return wext_ops.signal(ifname, buf);
}

static int ra_get_noise(const char *ifname, int *buf)
{
    return wext_ops.noise(ifname, buf);
}

static int ra_get_quality(const char *ifname, int *buf)
{
	return wext_ops.quality(ifname, buf);
}

static int ra_get_quality_max(const char *ifname, int *buf)
{
	return wext_ops.quality_max(ifname, buf);
}

static int ra_get_uptime(const char *ifname, int *buf)
{
	struct iwreq iwr;
    strncpy(iwr.ifr_name, ifname, sizeof(iwr.ifr_name));

	*buf = 0;
	memset(&iwr.u.ap_addr, 0, sizeof(iwr.u.ap_addr));
	if (iwinfo_ioctl(SIOCGIWAP, &iwr) >= 0)
	{
		*buf = ((uint8_t)iwr.u.ap_addr.sa_data[10]<<24) |
			((uint8_t)iwr.u.ap_addr.sa_data[11]<<16) |
			((uint8_t)iwr.u.ap_addr.sa_data[12]<<8) |
			((uint8_t)iwr.u.ap_addr.sa_data[13]<<0);

		return 0;
	}

	return -1;
}

static int ra_get_encryption(const char *ifname, char *buf)
{
	struct iwreq iwr;
	struct iwinfo_crypto_entry *c = (struct iwinfo_crypto_entry *)buf;

    strncpy(iwr.ifr_name, ifname, sizeof(iwr.ifr_name));
    iwr.u.data.pointer = (caddr_t)c;
    iwr.u.data.length = sizeof(struct iwinfo_crypto_entry);
    iwr.u.data.flags = 0x7470;

	if (iwinfo_ioctl(SIOCGIWENCODE, &iwr) == 0)
	{
		return 0;
	}

	return -1;
}

static int ra_get_phyname(const char *ifname, char *buf)
{
	strcpy(buf, ifname);

	return 0;
}

static int ra_get_assoclist(const char *ifname, char *buf, int *len)
{
	struct iwreq iwr;
	struct iwinfo_assoclist_entry entry[128];

    strncpy(iwr.ifr_name, ifname, sizeof(iwr.ifr_name));
    iwr.u.data.pointer = (caddr_t)&entry;
    iwr.u.data.length = sizeof(entry);
    iwr.u.data.flags = 0x7470;

	if (iwinfo_ioctl(IEEE80211_IOCTL_STA_INFO, &iwr) == 0)
	{
		memcpy(buf, &entry, iwr.u.data.length);
		*len = iwr.u.data.length;
		return 0;
	}

	return -1;
}

static int ra_get_txpwrlist(const char *ifname, char *buf, int *len)
{
    return wext_ops.txpwrlist(ifname, buf, len);
}

static int ra_get_scanlist(const char *ifname, char *buf, int *len)
{
	return wext_ops.scanlist(ifname, buf, len);
}

uint8_t ra_restricted(uint8_t flag) {
	int noht20 = !!(flag & CHANNEL_DISABLED);
	int noht40 = !(flag & CHANNEL_40M_CAP);
	int noht80 = !(flag & (CHANNEL_40M_CAP));
	int chandfs = !!(flag & CHANNEL_RADAR);
	int chanradar = !!(flag & CHANNEL_RADAR);
	int chansta = !!(flag & CHANNEL_NO_IBSS);
	int chanadhoc = !!(flag & CHANNEL_NO_IBSS);

	return (noht80 << 7) | (noht40 << 6) | (noht20 << 5) |
		(chandfs << 0) | (chanradar << 1) | (chansta << 2) | (chanadhoc << 3);
}

static int ra_get_freqlist(const char *ifname, char *buf, int *len)
{
	struct iwreq wrq;
	struct iw_range range;
	struct iwinfo_freqlist_entry entry;
	int i, bl;

	wrq.u.data.pointer = (caddr_t) &range;
	wrq.u.data.length  = sizeof(struct iw_range);
	wrq.u.data.flags   = 0;
	strncpy(wrq.ifr_name, ifname, IFNAMSIZ);

	if(iwinfo_ioctl(SIOCGIWRANGE, &wrq) >= 0)
	{
		bl = 0;

		for(i = 0; i < range.num_frequency; i++)
		{
			entry.mhz		 = ra_freq2mhz(&range.freq[i]);
			entry.channel	 = range.freq[i].i;
			entry.restricted = ra_restricted(range.freq[i].flags);

			memcpy(&buf[bl], &entry, sizeof(struct iwinfo_freqlist_entry));
			bl += sizeof(struct iwinfo_freqlist_entry);
		}

		*len = bl;
		return 0;
	}

	return -1;
}


static int ra_get_country(const char *ifname, char *buf)
{
    return wext_ops.country(ifname, buf);
}

static int ra_get_countrylist(const char *ifname, char *buf, int *len)
{
	int i, count;
	COUNTRY_CODE_TO_COUNTRY_REGION *e, *p = NULL;
	struct iwinfo_country_entry *c = (struct iwinfo_country_entry *)buf;

	count = 0;

	for( int i = 0; i < (sizeof(allCountry)/sizeof(allCountry[0])); i++ )
	{
		e = &allCountry[i];

		if( !p || strcmp(e->IsoName, p->IsoName) )
		{
			c->iso3166 = ((e->IsoName[0]<<8)|(e->IsoName[1]));
			snprintf(c->ccode, sizeof(c->ccode), "%i", e->CountryNum);

			c++;
			count++;
		}

		p = e;
	}

	*len = (count * sizeof(struct iwinfo_country_entry));
	return 0;
}

static int ra_get_hwmodelist(const char *ifname, int *buf)
{
    return wext_ops.hwmodelist(ifname, buf);
}

static int ra_get_htmodelist(const char *ifname, int *buf)
{
	/* Stub */
	return -1;
}

static int ra_get_mbssid_support(const char *ifname, int *buf)
{
	return -1;
}

static int ra_get_hardware_id(const char *ifname, char *buf)
{
	return wext_ops.hardware_id(ifname, buf);
}

static int ra_get_hardware_name(const char *ifname, char *buf)
{
	sprintf(buf, "Generic Ralink");
	return 0;
}

static int ra_get_txpower_offset(const char *ifname, int *buf)
{
	/* Stub */
	*buf = 0;
	return 0;
}

static int ra_get_frequency_offset(const char *ifname, int *buf)
{
	/* Stub */
	*buf = 0;
	return -1;
}

const struct iwinfo_ops ra_ops = {
	.name             = "ra",
	.probe            = ra_probe,
	.channel          = ra_get_channel,
	.frequency        = ra_get_frequency,
	.frequency_offset = ra_get_frequency_offset,
	.txpower          = ra_get_txpower,
	.txpower_offset   = ra_get_txpower_offset,
	.bitrate          = ra_get_bitrate,
	.signal           = ra_get_signal,
	.noise            = ra_get_noise,
	.quality          = ra_get_quality,
	.quality_max      = ra_get_quality_max,
	.uptime	 		  = ra_get_uptime,
	.mbssid_support   = ra_get_mbssid_support,
	.hwmodelist       = ra_get_hwmodelist,
	.htmodelist       = ra_get_htmodelist,
	.mode             = ra_get_mode,
	.ssid             = ra_get_ssid,
	.bssid            = ra_get_bssid,
	.country          = ra_get_country,
	.hardware_id      = ra_get_hardware_id,
	.hardware_name    = ra_get_hardware_name,
	.encryption       = ra_get_encryption,
	.phyname          = ra_get_phyname,
	.assoclist        = ra_get_assoclist,
	.txpwrlist        = ra_get_txpwrlist,
	.scanlist         = ra_get_scanlist,
	.freqlist         = ra_get_freqlist,
	.countrylist      = ra_get_countrylist,
	.close            = ra_close
};
