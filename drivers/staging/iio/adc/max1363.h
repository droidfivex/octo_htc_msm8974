#ifndef _MAX1363_H_
#define  _MAX1363_H_

#define MAX1363_SETUP_BYTE(a) ((a) | 0x80)


#define MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_VDD	0x00
#define MAX1363_SETUP_AIN3_IS_REF_EXT_TO_REF	0x20
#define MAX1363_SETUP_AIN3_IS_AIN3_REF_IS_INT	0x40
#define MAX1363_SETUP_AIN3_IS_REF_REF_IS_INT	0x60
#define MAX1363_SETUP_POWER_UP_INT_REF		0x10
#define MAX1363_SETUP_POWER_DOWN_INT_REF	0x00

#define MAX1363_SETUP_EXT_CLOCK			0x08
#define MAX1363_SETUP_INT_CLOCK			0x00
#define MAX1363_SETUP_UNIPOLAR			0x00
#define MAX1363_SETUP_BIPOLAR			0x04
#define MAX1363_SETUP_RESET			0x00
#define MAX1363_SETUP_NORESET			0x02
#define MAX1363_SETUP_MONITOR_SETUP		0x01

#define MAX1363_MON_RESET_CHAN(a) (1 << ((a) + 4))
#define MAX1363_MON_INT_ENABLE			0x01

#define MAX1363_CONFIG_BYTE(a) ((a))

#define MAX1363_CONFIG_SE			0x01
#define MAX1363_CONFIG_DE			0x00
#define MAX1363_CONFIG_SCAN_TO_CS		0x00
#define MAX1363_CONFIG_SCAN_SINGLE_8		0x20
#define MAX1363_CONFIG_SCAN_MONITOR_MODE	0x40
#define MAX1363_CONFIG_SCAN_SINGLE_1		0x60
#define MAX1236_SCAN_MID_TO_CHANNEL		0x40

#define MAX1363_CONFIG_EN_MON_MODE_READ 0x18

#define MAX1363_CHANNEL_SEL(a) ((a) << 1)

#define MAX1363_CHANNEL_SEL_MASK		0x1E
#define MAX1363_SCAN_MASK			0x60
#define MAX1363_SE_DE_MASK			0x01

#define MAX1363_MAX_CHANNELS 25
struct max1363_mode {
	int8_t		conf;
	DECLARE_BITMAP(modemask, MAX1363_MAX_CHANNELS);
};

enum max1363_modes {
	
	_s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7, _s8, _s9, _s10, _s11,
	
	d0m1, d2m3, d4m5, d6m7, d8m9, d10m11,
	d1m0, d3m2, d5m4, d7m6, d9m8, d11m10,
	
	s0to1, s0to2, s2to3, s0to3, s0to4, s0to5, s0to6,
	s6to7, s0to7, s6to8, s0to8, s6to9,
	s0to9, s6to10, s0to10, s6to11, s0to11,
	
	d0m1to2m3, d0m1to4m5, d0m1to6m7, d6m7to8m9,
	d0m1to8m9, d6m7to10m11, d0m1to10m11, d1m0to3m2,
	d1m0to5m4, d1m0to7m6, d7m6to9m8, d1m0to9m8,
	d7m6to11m10, d1m0to11m10,
};

struct max1363_chip_info {
	const struct iio_info		*info;
	struct iio_chan_spec *channels;
	int num_channels;
	const enum max1363_modes	*mode_list;
	enum max1363_modes		default_mode;
	u16				int_vref_mv;
	u8				num_modes;
	u8				bits;
};

struct max1363_state {
	struct i2c_client		*client;
	u8				setupbyte;
	u8				configbyte;
	const struct max1363_chip_info	*chip_info;
	const struct max1363_mode	*current_mode;
	u32				requestedmask;
	struct regulator		*reg;

	bool				monitor_on;
	unsigned int			monitor_speed:3;
	u8				mask_high;
	u8				mask_low;
	
	s16				thresh_high[8];
	s16				thresh_low[8];
};

const struct max1363_mode
*max1363_match_mode(const unsigned long *mask,
		    const struct max1363_chip_info *ci);

int max1363_set_scan_mode(struct max1363_state *st);

#ifdef CONFIG_MAX1363_RING_BUFFER
int max1363_update_scan_mode(struct iio_dev *indio_dev,
			     const unsigned long *scan_mask);
int max1363_register_ring_funcs_and_init(struct iio_dev *indio_dev);
void max1363_ring_cleanup(struct iio_dev *indio_dev);

#else 
int max1363_update_scan_mode(struct iio_dev *indio_dev,
			     const long *scan_mask)
{
	return 0;
}

static inline int
max1363_register_ring_funcs_and_init(struct iio_dev *indio_dev)
{
	return 0;
}

static inline void max1363_ring_cleanup(struct iio_dev *indio_dev)
{
}
#endif 
#endif 
