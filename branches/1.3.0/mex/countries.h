/*
 * Here are some things we use in dealing with the ... data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define CNULL             ((char *)NULL)
#define VNULL             ((void *)NULL)
#define N_CONTINENTS		8
#define N_EURO			48
#define N_AFR			63
#define N_ANTARCTICA		2
#define N_ASIA			55
#define N_AUSTRALASIA		34
#define N_CENTRAL_AM		30
#define N_SOUTH_AM		18
#define N_NORTH_AM		4
#define N_COUNTRIES	N_EURO + N_AFR + N_ANTARCTICA + N_ASIA + N_AUSTRALASIA + N_CENTRAL_AM + N_SOUTH_AM + N_NORTH_AM

#ifndef M_PI
#define M_PI          3.14159265358979323846
#endif

struct	POINT {
	float	x;
	float	y;
};

struct COUNTRY_HEADER {
	short int country_id;		/* Country ID number */
	int n;				/* number of points in polygon */
	short int greenwich;  		/* Greenwich is TRUE if Greenwich is crossed */
	float west, east, south, north;	/* polygon limits */
	float area;    			/* Area of polygon */
	struct POINT	centroid;	/* to hold the polygon centroid coords */
};

void *GMT_memory (void *prev_addr, size_t nelem, size_t size, char *progname) {
	void *tmp;
	static char *m_unit[4] = {"bytes", "kb", "Mb", "Gb"};
	double mem;
	int k;

	if (nelem == 0) return(VNULL); /* Take care of n = 0 */
	
	if (nelem < 0) { /* This is illegal and caused by upstream bugs in GMT */
		fprintf (stderr, "GMT Fatal Error: %s requesting memory for a negative number of items [n_items = %d]\n", progname, (int)nelem);
		exit (EXIT_FAILURE);
	}
	
	if (prev_addr) {
		if ((tmp = realloc ((void *) prev_addr, (size_t)(nelem * size))) == VNULL) {
			mem = (double)(nelem * size);
			k = 0;
			while (mem >= 1024.0 && k < 3) mem /= 1024.0, k++;
			fprintf (stderr, "GMT Fatal Error: %s could not reallocate memory [%.2f %s, n_items = %d]\n", progname, mem, m_unit[k], (int)nelem);
			exit (EXIT_FAILURE);
		}
	}
	else {
		if ((tmp = calloc ((size_t) nelem, (unsigned) size)) == VNULL) {
			mem = (double)(nelem * size);
			k = 0;
			while (mem >= 1024.0 && k < 3) mem /= 1024.0, k++;
			fprintf (stderr, "GMT Fatal Error: %s could not allocate memory [%.2f %s, n_items = %d]\n", progname, mem, m_unit[k], (int)nelem);
			exit (EXIT_FAILURE);
		}
	}
	return (tmp);
}

char *continent_list[N_CONTINENTS] = {
	"africa",
	"antarctica",
	"asia",
	"australasia",
	"central_america",
	"south_america",
	"europe",
	"north_america",
};

char *afric_country_list[N_AFR] = {
	"algeria",
	"angola",
	"benin",
	"botswana",
	"burkina_faso",
	"burundi",
	"cabo_verde",
	"cameroon",
	"canarias",
	"central_african_rep",
	"chad",
	"comoros",
	"congo",
	"djibouti",
	"egypt",
	"equatorial_guinea",
	"eritrea",
	"ethiopia",
	"europa_island",
	"gabon",
	"gambia",
	"ghana",
	"guine-bissau",
	"guinea",
	"ivory_coast",
	"juan",
	"kenya",
	"lesotho",
	"liberia",
	"libya",
	"madagascar",
	"madeira",
	"malawi",
	"mali",
	"mauritania",
	"mauritius",
	"mayotte",
	"morocco",
	"mozambique",
	"namibia",
	"niger",
	"nigeria",
	"reunion",
	"rwanda",
	"sao_tome_e_princepe",
	"senegal",
	"seychelles",
	"sierra_leone",
	"somalia",
	"south_africa",
	"st_helena",
	"sudan",
	"swaziland",
	"tanzania",
	"togo",
	"tristao_da_cunha",
	"tromelin_island",
	"tunisia",
	"uganda",
	"western_sahara",
	"zaire",
	"zambia",
	"zimbabwe",
};

char *antarctica_country_list[N_ANTARCTICA] = {
	"antarctica",
	"heard_and_McDonald",
};

char *asia_country_list[N_ASIA] = {
	"afghanistan",
	"aleutian180",
	"armenia",
	"azerbaijan",
	"bahrain",
	"bangladesh",
	"bhutan",
	"brunei",
	"burma_myanmar",
	"cambodia",
	"china",
	"christmas_island",
	"gaza_strip",
	"hong_kong",
	"india",
	"iran",
	"iraq",
	"israel",
	"japan",
	"jordan",
	"kazakhstan",
	"kuwait",
	"kyrgyzstan",
	"laos",
	"lebanon",
	"macau",
	"macedonia",
	"malaysia",
	"maldives",
	"mongolia",
	"montenegro",
	"nepal",
	"north_korea",
	"oman",
	"pakistan",
	"paracel_islands",
	"philippines",
	"qatar",
	"russia",
	"saudi_arabia",
	"singapore",
	"south_korea",
	"spratly_islands",
	"sri_lanka",
	"syria",
	"taiwan",
	"tajikistan",
	"thailand",
	"turkey",
	"turkmenistan",
	"united_arab_emirates",
	"uzebkistan",
	"vietnam",
	"west_bank",
	"yemen",
};

char *australasia_country_list[N_AUSTRALASIA] = {
	"australia",
	"baker_island",
	"cocos_islands",
	"clipperton",
	"cook_islands",
	"fiji",
	"french_polynesia",
	"guam",
	"howland_island",
	"indonesia",
	"jarvis_island",
	"kiribati",
	"mariana",
	"micronesia",
	"midway_islands",
	"nauru",
	"new_caledonia",
	"new_zealand",
	"niue",
	"norfolk_island",
	"palmyra_atoll",
	"papua_new_guinea",
	"pitcairn_island",
	"republic_of_palau",
	"solomon_islands",
	"tasmania",
	"timor_leste",
	"tonga",
	"trust_territory",
	"tuvalu",
	"vanuatu",
	"wake_island",
	"wallis",
	"western_samoa",
};

char *central_america_country_list[N_CENTRAL_AM] = {
	"anguilla",
	"antigua",
	"bahamas",
	"barbados",
	"belize",
	"bermuda",
	"british_virgin_islands",
	"cayman_islands",
	"costa_rica",
	"cuba",
	"dominica",
	"dominican_rep",
	"el_salvador",
	"french_antilles",
	"grenada",
	"guadeloupe",
	"guatemala",
	"haiti",
	"honduras",
	"jamaica",
	"martinique",
	"mexico",
	"montserrat",
	"navassa_island",
	"nicaragua",
	"panama",
	"puerto_rico",
	"st_lucia",
	"st_vincent",
	"virgin_islands",
};
char *south_america_country_list[N_SOUTH_AM] = {
	"argentina",
	"bolivia",
	"brazil",
	"chile",
	"colombia",
	"easter_island",
	"ecuador",
	"falkland_islands",
	"french_guiana",
	"galapagos",
	"guyana",
	"netherlands_antilles",
	"paraguay",
	"peru",
	"surinam",
	"trinidad",
	"uruguay",
	"venezuela",
};

char *euro_country_list[N_EURO] = {
	"acores",
	"albania",
	"andorra",
	"austria",
	"belarus",
	"belgium",
	"bosnia_herzegovinia",
	"bulgaria",
	"croatia",
	"cyprus",
	"czech_republic",
	"denmark",
	"estonia",
	"faeroe_islands",
	"finland",
	"france",
	"georgia_ssr",
	"germany",
	"gibraltar",
	"greece",
	"greenland",
	"hungary",
	"iceland",
	"ireland",
	"italy",
	"jan_mayen",
	"latvia",
	"liechtenstein",
	"lithuania",
	"luxembourg",
	"malta",
	"moldova",
	"monaco",
	"netherlands",
	"norway",
	"poland",
	"portugal",
	"romania",
	"san_marino",
	"serbia",
	"slovakia",
	"slovenia",
	"spain",
	"svalbard",
	"sweden",
	"switzerland",
	"ukraine",
	"united_kingdom",
};

char *north_america_country_list[N_NORTH_AM] = {
	"american_samoa",
	"canada",
	"st_pierre",
	"u_s_a",
};

char *country_list[N_COUNTRIES] = {
	"acores",
	"afghanistan",
	"albania",
	"aleutian180",
	"algeria",
	"american_samoa",
	"andorra",
	"angola",
	"anguilla",
	"antarctica",
	"antigua",
	"argentina",
	"armenia",
	"australia",
	"austria",
	"azerbaijan",
	"bahamas",
	"bahrain",
	"baker_island",
	"bangladesh",
	"barbados",
	"belarus",
	"belgium",
	"belize",
	"benin",
	"bermuda",
	"bhutan",
	"bolivia",
	"bosnia_herzegovinia",
	"botswana",
	"brazil",
	"british_virgin_islands",
	"brunei",
	"bulgaria",
	"burkina_faso",
	"burma_myanmar",
	"burundi",
	"cabo_verde",
	"cambodia",
	"cameroon",
	"canada",
	"canarias",
	"cayman_islands",
	"central_african_rep",
	"chad",
	"chile",
	"china",
	"christmas_island",
	"clipperton",
	"cocos_islands",
	"colombia",
	"comoros",
	"congo",
	"cook_islands",
	"costa_rica",
	"croatia",
	"cuba",
	"cyprus",
	"czech_republic",
	"denmark",
	"djibouti",
	"dominica",
	"dominican_rep",
	"easter_island",
	"ecuador",
	"egypt",
	"el_salvador",
	"equatorial_guinea",
	"eritrea",
	"estonia",
	"ethiopia",
	"europa_island",
	"faeroe_islands",
	"falkland_islands",
	"fiji",
	"finland",
	"france",
	"french_antilles",
	"french_guiana",
	"french_polynesia",
	"gabon",
	"galapagos",
	"gambia",
	"gaza_strip",
	"georgia_ssr",
	"germany",
	"ghana",
	"gibraltar",
	"greece",
	"greenland",
	"grenada",
	"guadeloupe",
	"guam",
	"guatemala",
	"guine-bissau",
	"guinea",
	"guyana",
	"haiti",
	"heard_and_McDonald",
	"honduras",
	"hong_kong",
	"howland_island",
	"hungary",
	"iceland",
	"india",
	"indonesia",
	"iran",
	"iraq",
	"ireland",
	"israel",
	"italy",
	"ivory_coast",
	"jamaica",
	"jan_mayen",
	"japan",
	"jarvis_island",
	"jordan",
	"juan",
	"kazakhstan",
	"kenya",
	"kiribati",
	"kuwait",
	"kyrgyzstan",
	"laos",
	"latvia",
	"lebanon",
	"lesotho",
	"liberia",
	"libya",
	"liechtenstein",
	"lithuania",
	"luxembourg",
	"macau",
	"macedonia",
	"madagascar",
	"madeira",
	"malawi",
	"malaysia",
	"maldives",
	"mali",
	"malta",
	"mariana",
	"martinique",
	"mauritania",
	"mauritius",
	"mayotte",
	"mexico",
	"micronesia",
	"midway_islands",
	"moldova",
	"monaco",
	"mongolia",
	"montenegro",
	"montserrat",
	"morocco",
	"mozambique",
	"namibia",
	"nauru",
	"navassa_island",
	"nepal",
	"netherlands",
	"netherlands_antilles",
	"new_caledonia",
	"new_zealand",
	"nicaragua",
	"niger",
	"nigeria",
	"niue",
	"norfolk_island",
	"north_korea",
	"norway",
	"oman",
	"pakistan",
	"palmyra_atoll",
	"panama",
	"papua_new_guinea",
	"paracel_islands",
	"paraguay",
	"peru",
	"philippines",
	"pitcairn_island",
	"poland",
	"portugal",
	"puerto_rico",
	"qatar",
	"republic_of_palau",
	"reunion",
	"romania",
	"russia",
	"rwanda",
	"san_marino",
	"sao_tome_e_princepe",
	"saudi_arabia",
	"senegal",
	"serbia",
	"seychelles",
	"sierra_leone",
	"singapore",
	"slovakia",
	"slovenia",
	"solomon_islands",
	"somalia",
	"south_africa",
	"south_korea",
	"spain",
	"spratly_islands",
	"sri_lanka",
	"st_helena",
	"st_lucia",
	"st_pierre",
	"st_vincent",
	"sudan",
	"surinam",
	"svalbard",
	"swaziland",
	"sweden",
	"switzerland",
	"syria",
	"taiwan",
	"tajikistan",
	"tanzania",
	"tasmania",
	"thailand",
	"timor_leste",
	"togo",
	"tonga",
	"trinidad",
	"tristao_da_cunha",
	"tromelin_island",
	"trust_territory",
	"tunisia",
	"turkey",
	"turkmenistan",
	"tuvalu",
	"u_s_a",
	"uganda",
	"ukraine",
	"united_arab_emirates",
	"united_kingdom",
	"uruguay",
	"uzebkistan",
	"vanuatu",
	"venezuela",
	"vietnam",
	"virgin_islands",
	"wake_island",
	"wallis",
	"west_bank",
	"western_sahara",
	"western_samoa",
	"yemen",
	"zaire",
	"zambia",
	"zimbabwe",
};
