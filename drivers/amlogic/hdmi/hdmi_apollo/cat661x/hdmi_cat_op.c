
#include <linux/kthread.h>
    
#include "hdmi_cat_defstx.h"
#include "hdmi_i2c.h"
#include "hdmi_cat_interrupt.h"
#include "hdmi_cat_mddc.h"
#include "hdmi_cat_audio.h"
#include "hdmi_cat_video.h"
#include "hdmi_cat_edid.h"
#include "hdmi_cat_hdcp.h"
#include "hdmi_cat_info_set.h"
    
#include "hdmi_debug.h"
#include "hdmi_module.h"
    
#include "hdmi_video.h"
    
#define HDMI_CHIP_HANDLE_MAGIC	0x48444D49	//ASCII of "HDMI" 
    
//extern gpio_hw_info_t hdmi_gpio_hw_info;


				     unsigned char tv_mode);



{
	
	WriteByteHDMITX_CAT(REG_AV_MUTE, B_SET_AVMUTE);
	
	return 0;


{
	
	WriteByteHDMITX_CAT(REG_AV_MUTE, B_CLR_AVMUTE);
	
	return 0;



//-------------------------------------------------------------------
static int hdmi_cat6611_SW_ResetHDMITX(void)	//it don't modify the register you can write, reset some FIFO
{
	
			     B_REF_RST | B_AREF_RST | B_VID_RST | B_AUD_RST |
			     B_HDCP_RST);
	
	
	
	    //Reset signal for HDMI_TX_DRV. '1': all flip-flops in the transmitter, including those in the BIST pattern generator, are reset. 
	    WriteByteHDMITX_CAT(REG_AFE_DRV_CTRL, B_AFE_DRV_RST);	// Avoid power loading in un play status.
	



//---------------------------------------------------------------------------
static void hdmi_cat6611_HW_Reset_HDMI(Hdmi_info_para_t * info) 
{
	
	
	
	
	AVTimeDly(32);

{
	
	
	     && (info->audio_flag & 0x1))
		
		
		    //The valid bit for channel 2/1 is defined in reg191[2], Valid bit should be set to ��1�� if the corresponding audio channel maps to the NLPCM audio source.
		    
		CAT_EnableAudioOutput(info);
		
		
//       hdmi_cat6611_ClearAVmute(info);  
//       WriteByteHDMITX_CAT(REG_SW_RST, ~(B_AUD_RST|B_AREF_RST)); //enable audio(bit4==0: Software Audio clock base signal reset, bit2: Audio FIFO reset.)
		}
	
	else
		
		
		
	



//unsigned audio_fifo_overflow_count = 0;
//unsigned audio_cts_error_count = 0;
//unsigned auth_fail_overflow_count = 0;

{
	
	
	
	0, 0, 0};
	
	
	    ((sysstat & (B_HPDETECT | B_RXSENDETECT)) ==
	     (B_HPDETECT | B_RXSENDETECT)) ? 1 : 0;
	
		
		
		
		
	
	
		
		
//         hdmi_dbg_print("there is some INT .\n");
		    if (interrupt_flag[0] & (B_INT_HPD_PLUG | B_INT_RX_SENSE))
			
			
			
		
			
			
			
//                                       audio_fifo_overflow_count++;
			}
		
			
			
			
//                                       audio_cts_error_count++;
			}
		
			
			
//                       hdmi_dbg_print("DDC FIFO Error.\n");
			    CAT_ClearDDCFIFO();
			
		
			
			
//                       hdmi_dbg_print("DDC BUS HANG.\n") ;
			    CAT_AbortDDC();
			
			     && (info->output_state == CABLE_PLUGIN_HDMI_OUT))
				
			
		
			
			
//            hdmi_dbg_print("interrupt Authenticate Done.\n") ; 
			    hdmi_cat6611_ClearAVmute(info);
			
			
			
			
		
			
			
//            hdmi_dbg_print("interrupt Authenticate Fail.\n") ;        
			    CAT_AbortDDC();	//del by xintan
//            WriteByteHDMITX_CAT(REG_SW_RST, (ReadByteHDMITX_CAT(REG_SW_RST))& (~B_CPDESIRE));
//            interrupt_mask_[1] = B_AUTH_DONE_MASK; 
			if ((info->auto_ri_flag == 1)
			    && (info->output_state == CABLE_PLUGIN_HDMI_OUT))
				
				
				
				
			
			else
				
				
				
			
		
			
			
				
				
				
			
		
		
		
		sysstat = ReadByteHDMITX_CAT(REG_SYS_STATUS);
		
		
		sysstat &= ~(B_INTACTDONE | B_CLR_AUD_CTS);
		
		}
	
	else
		
		
		{
			
					     B_AREF_RST | B_VID_RST | B_AUD_RST
					     | B_HDCP_RST);
			
			
					     B_AFE_DRV_RST | B_AFE_DRV_PWD);
		
		
		
		
		}


{
	
	
//       unsigned char interrupt_flag[3] = {0, 0, 0};
	unsigned char intdata[3] = { 0, 0, 0 };
	
	
	ReadBlockHDMITX_CAT(REG_INT_STAT1, 3, intdata);
	
	    //hdmi_dbg_print("INT_Handler: reg%02x = %02x\n", REG_INT_STAT1, sysstat) ;
	    //hdmi_dbg_print("info->hpd_state= %02x\n", info->hpd_state) ;
	    if (sysstat & B_INT_ACTIVE)
		
		
			
			
			
			
		
			
			
			
			
//        if( info->hpd_state )
//         {
//             // when DDC hang, and aborted DDC, the HDCP authentication need to restart.
//             CAT_HDCP_ResumeAuthentication(info) ;
//          }
			}
		
			
			
			
			{
				
						     (ReadByteHDMITX_CAT
						      (REG_SW_RST)) | B_AREF_RST
						     | B_VID_RST | B_AUD_RST |
						     B_HDCP_RST);
				
				
				    //bit4: all flip-flops in the transmitter, including those in the BIST pattern generator, are reset.
				    //bit5: all flip-flops in the transmitter are reset while all other analog parts are powered off.
				    WriteByteHDMITX_CAT(REG_AFE_DRV_CTRL, B_AFE_DRV_RST | B_AFE_DRV_PWD);	//Reset signal for HDMI_TX_DRV.
//             printf("Unplug, %x %x\n", ReadByteHDMITX_CAT(REG_SW_RST), ReadByteHDMITX_CAT(REG_AFE_DRV_CTRL)) ;
			
			
			else	//hotplug
			{
			
			
		
			
			
				
				
				
			
		
		
		
		
		
		
		
		
		}
	
	else
		
		
			
		
		{
			
					     B_AREF_RST | B_VID_RST | B_AUD_RST
					     | B_HDCP_RST);
			
			
					     B_AFE_DRV_RST | B_AFE_DRV_PWD);
			
//            printf("Unplug, %x %x\n", ReadByteHDMITX_CAT(REG_SW_RST), ReadByteHDMITX_CAT(REG_AFE_DRV_CTRL)) ;
		
		
	


{
	
	
		
		
			
			
			
		
		
	
	else
		


{
	
	
		err = CAT_ProgramSyncEmbeddedVideoMode(info);	// if CCIR656 input
	if ((info->output_state == CABLE_PLUGIN_HDMI_OUT)
	    || (info->output_state == CABLE_PLUGIN_DVI_OUT))
		
		
		
		
		
//      hdmi_cat6611_ClearAVmute(info);
		    err = 0;
		
	
	else
		
		
		
		
		
	



#define PRINTF_REG_MSN
#ifdef PRINTF_REG_MSN
unsigned char register_msg_flag = 0;


{
	
	
	
		
		
		
	
	
		
		
			
			
			    ReadByteHDMITX_CAT((unsigned char)((i + j) & 0xFF));
			
		
	
		
		
			
			
			    ReadByteHDMITX_CAT((unsigned char)((i + j) & 0xFF));
			
		

#endif	/* 
    
//---------------------------------------------------------------------------
void hdmi_cat6611_InitUNPLUG(Hdmi_info_para_t * info) 
{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	    //1: disable this interrupt; 0: Enable this interrupt
	    abData[0] =
	    B_AUDIO_OVFLW_MASK | B_DDC_NOACK_MASK | B_DDC_NOACK_MASK |
	    B_DDC_BUS_HANG_MASK;
	
	    B_PKT_AVI_MASK | B_PKT_ISRC_MASK | B_PKT_ACP_MASK | B_PKT_NULL_MASK
	    | B_PKT_GEN_MASK | B_KSVLISTCHK_MASK | B_AUTH_DONE_MASK |
	    B_AUTH_FAIL_MASK;
	
	    B_AUDCTS_MASK | B_VSYNC_MASK | B_VIDSTABLE_MASK | B_PKT_MPG_MASK |
	    B_PKT_SPD_MASK | B_PKT_AUD_MASK;
	
	
	
//   printf("(InitDVITX)is Done\n");           
} 
{
	
	
	
	hdmi_dbg_print("(InitHDMITX)is starting\n");
	
	
	
	
	
	
	
//    if(hdmi_gpio_hw_info.interrupt_pol)
//      WriteByteHDMITX_CAT(REG_INT_CTRL, B_INTPOL_ACTL | B_INTPOL_ACTH) ; // depends on the interrupt type: higth acitve 
//    else
//      WriteByteHDMITX_CAT(REG_INT_CTRL, 0) ; // depends on the interrupt type: low acitve      
	    
	
	
//    id_device = ReadWordHDMITX_CAT(REG_VENDOR_ID0); 
//    id_device = ReadWordHDMITX_CAT(REG_DEVICE_ID0);
	    
	WriteByteHDMITX_CAT(REG_ACP_CTRL, 0);	//disable PktACP packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_ISRC1_CTRL, 0);	//disable PktISRC1 packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_ISRC2_CTRL, 0);	//disable PktISRC2 packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_AVI_INFOFRM_CTRL, 0);	//disable PktAVI packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_AUD_INFOFRM_CTRL, 0);	//disable PktAUO packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_SPD_INFOFRM_CTRL, 0);	//disable PktSPD packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	WriteByteHDMITX_CAT(REG_MPG_INFOFRM_CTRL, 0);	//disable PktMPG packet sending & repeat. bit0: enable/diable sending; bit1: enable/disble repeat
	
	
	
	
		
		
			
			
			
			
			
//            info->output_state = CABLE_PLUGIN_DVI_OUT ;
			}
		
//        if(info->support_ycbcr444_flag == 1)
//               info->videopath_outindex = 1;    // Video Output Color Space Conversion : 0 - RGB out; 1 - YCbr (4:4:4) out; 2 - YCbr (4:2:2) out;   
		    
		
		
			
		
		else
			
			
			
		
		
		
		    //1: disable this interrupt; 0: Enable this interrupt
		    abData[0] = B_DDC_NOACK_MASK | B_DDC_FIFO_ERR_MASK;
		
		     && (info->output_state == CABLE_PLUGIN_HDMI_OUT))
			
			    B_PKT_AVI_MASK | B_PKT_ISRC_MASK | B_PKT_ACP_MASK |
			    B_PKT_NULL_MASK | B_PKT_GEN_MASK;
		
		else
			
			    B_PKT_AVI_MASK | B_PKT_ISRC_MASK | B_PKT_ACP_MASK |
			    B_PKT_NULL_MASK | B_PKT_GEN_MASK | B_AUTH_FAIL_MASK
			    | B_AUTH_DONE_MASK;
		
//      abData[2] = B_AUDCTS_MASK | B_VSYNC_MASK | B_PKT_MPG_MASK | B_PKT_SPD_MASK | B_PKT_AUD_MASK; 
		    abData[2] =
		    B_VSYNC_MASK | B_PKT_MPG_MASK | B_PKT_SPD_MASK |
		    B_PKT_AUD_MASK;
		
		
		
#ifdef PRINTF_REG_MSN    
		    CAT_DumpCat6611Reg();
		
#endif	/* 
		    info->init_hdmi_flag = 0;
		
	
	else			// unplug mode, ...
	{
		
	
	
	


{
	
	    //FIXME:whic register should good for detect the hdmi phy?
	int vid, did;
	
	
	
	
	
	
	    //Here should be the true device id---
	    return (vid == 0xffff && did == 0xffff) ? -1 : 0;



//unsigned audio_fifo_overflow_count = 0;
//unsigned audio_cts_error_count = 0;
//unsigned auth_fail_overflow_count = 0;


{
    Hdmi_info_para_t * info = data;
    struct hdmi_priv *priv = info->priv;
    unsigned char sysstat;
    unsigned char interrupt_mask[3];
    unsigned char err;

#ifdef PRINTF_REG_MSN
    unsigned char temp_test[8];
    unsigned char test_Addr;
    unsigned short test_NBytes;
#endif/* 

    //unsigned char audio_temp[12];  
    int video_fd;

    // video_appmode_t video_appmode;
    //if(hdmi_gpio_hw_info.interrupt_flag)
    //   AVEnableIrq(info->irq_flag); 
    video_fd = 0;
    err = 0;
    while (priv->i2c == NULL)
    {
        priv->i2c = hdmi_i2c_init_adapter();
        if (kthread_should_stop())
            return 0;
        msleep(1000);   //waiting utill i2c ready;
    }
    
    while (detecte_hdmi_phy() != 0)
    {
        HDMI_ERR("Can't detected a cat661x device,connect error or no device!\n");
        hdmi_i2c_release_adapter(priv->i2c);
        priv->i2c = NULL;
        kthread_should_stop();
        priv->task = NULL;
        return 0;
    }
    
    hdmi_cat6611_InitHDMITX(&priv->hinfo);
    msleep(10);
    while (!kthread_should_stop())
    {
        sysstat = 0;

#ifdef PRINTF_REG_MSN   
        temp_test[0] = 0;
        temp_test[1] = 0;
        temp_test[2] = 0;
        temp_test[3] = 0;
        temp_test[4] = 0;
        temp_test[5] = 0;
        temp_test[6] = 0;
        temp_test[7] = 0;
#endif  /* 

        check_cat6611_interrupt_status(info);
        if (info->hpd_state == 1)
        {
            check_video_format_hdmi(info, hdmi_get_tv_mode(info));
        }

        // hdmi_dbg_print("info->hpd_change_flag=%d,in[%d]\n",info->hpd_change_flag,__LINE__);  
        if ((info->hpd_change_flag == 1))
        {
            info->hpd_change_flag = 0;
            hdmi_dbg_print("video format changed.\n");
            sysstat = ReadByteHDMITX_CAT(REG_SYS_STATUS);
            
            if ((sysstat & (B_HPDETECT | B_RXSENDETECT)) 
                == (B_HPDETECT | B_RXSENDETECT))
            {
                if (info->init_hdmi_flag == 1)
                {
                    hdmi_cat6611_InitHDMITX(info);
                }
            }
            else
            {
                hdmi_cat6611_InitUNPLUG(info);
            }
        }
        
        if ((info->auto_ri_flag == 1)
            && (info->auth_state != HDCP_AUTHENTICATED)
            && (info->hpd_state == 1))
        {
            //auth_fail_overflow_count++;
            if ((info->auto_ri_flag == 1)
                && (info->output_state == CABLE_PLUGIN_HDMI_OUT))
                CAT_HDCP_ResumeAuthentication(info);
        }
        
        if ((info->video_mode_change_flag == 1))
        {
            WriteByteHDMITX_CAT(REG_SW_RST,
                B_REF_RST | B_AREF_RST | B_VID_RST | B_AUD_RST | B_HDCP_RST);
            AVTimeDly(1);
            WriteByteHDMITX_CAT(REG_SW_RST, B_AREF_RST | B_VID_RST | B_AUD_RST | B_HDCP_RST);	//The default value of chip power on state is 0x1C.                
            AVTimeDly(200);
            info->video_mode_change_flag = 0;

            if (info->hpd_state == 1)
            {
                hdmi_cat6611_SetAVmute(info);
                if ((info->tv_mode == HDMI_480I_60HZ)
                    || (info->tv_mode == HDMI_576I_50HZ))
                {
                    info->repeat_pixel_flag = 1;	// pixel repeat 1 time   
                }
                else
                {
                    info->repeat_pixel_flag = 0;	// no pixel repeat                                           
                }
                hdmi_cat6611_SetVideoPara(info);
                AVTimeDly(1);

                if (info->output_state == CABLE_PLUGIN_HDMI_OUT)
                {
                    CAT_EnableHDCP(info, info->auto_ri_flag);
                }
                else
                {
                    CAT_EnableHDCP(info, 0);
                }
                AVTimeDly(1);
                hdmi_cat6611_SetAudioPara(info);
                hdmi_cat6611_ClearAVmute(info);
                AVTimeDly(1);

                // 1: disable this interrupt; 0: Enable this interrupt
                interrupt_mask[0] = B_DDC_NOACK_MASK | B_DDC_FIFO_ERR_MASK;
                if ((info->auto_ri_flag == 1)
                    && (info->output_state == CABLE_PLUGIN_HDMI_OUT))
                {
                    interrupt_mask[1] =
                        B_PKT_AVI_MASK | B_PKT_ISRC_MASK |
                        B_PKT_ACP_MASK | B_PKT_NULL_MASK |
                        B_PKT_GEN_MASK;
                }
                else
                {
                    interrupt_mask[1] =
                        B_PKT_AVI_MASK | B_PKT_ISRC_MASK |
                        B_PKT_ACP_MASK | B_PKT_NULL_MASK |
                        B_PKT_GEN_MASK | B_AUTH_FAIL_MASK |
                        B_AUTH_DONE_MASK;
                }
               
                    B_VSYNC_MASK | B_PKT_MPG_MASK |
                    B_PKT_SPD_MASK | B_PKT_AUD_MASK;
                CAT_Set_Interrupt_Masks(interrupt_mask);
            }
        }
        
        if ((info->audio_fifo_overflow == 1)
            || (info->audio_cts_status_err_flag == 1))
        {
            //hdmi_dbg_print("audio error.\n");
            info->audio_fifo_overflow = 0;
            info->audio_cts_status_err_flag = 0;
            CAT6611_bPendingAudioAdjust = 1;
        }
        
        if (info->hpd_state == 1)
        {
            CAT_SetAudioChannel(info);
        }

#ifdef PRINTF_REG_MSN
        if (register_msg_flag == 1)
        {
            test_Addr = 0;
            test_NBytes = 1;
            ReadBlockHDMITX_CAT(test_Addr, test_NBytes, temp_test);
            WriteBlockHDMITX_CAT(test_Addr, test_NBytes, temp_test);
        }
        if (register_msg_flag == 2)
        {
            CAT_Switch_HDMITX_Bank(TX_SLV0, 1);
            test_Addr = 0;
            test_NBytes = 1;
            ReadBlockHDMITX_CAT(test_Addr, test_NBytes, temp_test);
            WriteBlockHDMITX_CAT(test_Addr, test_NBytes, temp_test);
            CAT_Switch_HDMITX_Bank(TX_SLV0, 0);
        }
        if (register_msg_flag == 3)
            CAT_DumpCat6611Reg();
#endif/* 

        AVTimeDly(500);
    }

    return 0;



//hdmi_cat6611_task_handle(Hdmi_info_para_t * info)
void start_hdmi_cat661x(struct hdmi_priv *priv) 
{
    priv->task = kthread_run(hdmi_cat6611_task_handle, &priv->hinfo, "kthread_hdmi");
}

void stop_hdmi_cat661x(struct hdmi_priv *priv) 
{
    if (priv->task)
        kthread_stop(priv->task);
}
