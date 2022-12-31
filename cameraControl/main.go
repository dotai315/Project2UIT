package main

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"io/ioutil"
	"log"
	"fmt"
	"encoding/json"
)

type videoXraw struct {
	Width     int    `json:"width"`
	Height    int    `json:"height"`
	Framerate int    `json:"framerate"`
	Format    string `json:"format"`
}

type videoXrawMemory struct {
	Width     int    `json:"width"`
	Height    int    `json:"height"`
	Framerate int    `json:"framerate"`
	Format    string `json:"format"`
}

type videoXrawH264 struct {
	Width         int    `json:"width"`
	Height        int    `json:"height"`
	Stream_format string `json:"stream_format"`
}

type nvarguscamerasrc struct {
	Name                 string          `json:"name"`
	Parent               string          `json:"parent"`
	Blocksize            uint            `json:"blocksize"`
	Num_buffers          int             `json:"num_buffers"`
	Typefind             bool            `json:"typefind"`
	Do_timestamp         bool            `json:"do_timestamp"`
	Silent               bool            `json:"silent"`
	Timeout              uint            `json:"timeout"`
	Wbmode               int             `json:"wbmode"`
	Saturation           float32         `json:"saturation"`
	Sensor_id            int             `json:"sensor_id"`
	Sensor_mode          int             `json:"sensor_mode"`
	Total_sensor_modes   int             `json:"total_sensor_modes"`
	Exposuretimerange    string          `json:"exposuretimerange"`
	Gainrange            string          `json:"gainrange"`
	Ispdigitalgainrange  string          `json:"ispdigitalgainrange"`
	Tnr_strength         float32         `json:"tnr_strength"`
	Tnr_mode             int             `json:"tnr_mode"`
	Ee_mode              int             `json:"ee_mode"`
	Ee_strength          float32         `json:"ee_strength"`
	Aeantibanding        int             `json:"aeantibanding"`
	Exposurecompensation float32         `json:"exposurecompensation"`
	Aelock               bool            `json:"aelock"`
	Aeregion             string          `json:"aeregion"`
	Awblock              bool            `json:"awblock"`
	Bufapi_version       bool            `json:"bufapi_version"`
	Video_xraw_memory    videoXrawMemory `json:"video_xraw_memory"`
}

type nvvidconv struct {
	Name                 string    `json:"name"`
	Parent               string    `json:"parent"`
	Qos                  bool      `json:"qos"`
	Silent               bool      `json:"silent"`
	Flip_method          int       `json:"flip_method"`
	Output_buffers       uint      `json:"output_buffers"`
	Interpolation_method int       `json:"interpolation_method"`
	Left                 int       `json:"left"`
	Right                int       `json:"right"`
	Top                  int       `json:"top"`
	Bottom               int       `json:"bottom"`
	B1_output            bool      `json:"b1_output"`
	Video_xraw           videoXraw `json:"video_xraw"`
}

type omxh264enc struct {
	Name                      string        `json:"name"`
	Parent                    string        `json:"parent"`
	Qos                       bool          `json:"qos"`
	Control_rate              int           `json:"control_rate"`
	Bitrate                   uint          `json:"bitrate"`
	Peak_bitrate              uint          `json:"peak_bitrate"`
	Quant_i_frames            uint          `json:"quant_i_frames"`
	Quant_p_frames            uint          `json:"quant_p_frames"`
	Quant_b_frames            uint          `json:"quant_b_frames"`
	Iframeinterval            uint          `json:"iframeinterval"`
	Sliceintrarefreshenable   bool          `json:"sliceintrarefreshenable"`
	Sliceintrarefreshinterval uint          `json:"sliceintrarefreshinterval"`
	Bit_packetization         bool          `json:"bit_packetization"`
	Vbv_size                  uint          `json:"vbv_size"`
	Temporal_tradeoff         int           `json:"temporal_tradeoff"`
	Enablemvbuffermeta        bool          `json:"enablemvbuffermeta"`
	Qp_range                  string        `json:"qp_range"`
	Measureencoderlatency     bool          `json:"measureencoderlatency"`
	Enabletwopasscbr          bool          `json:"enabletwopasscbr"`
	Preset_level              int           `json:"preset_level"`
	Enablestringerbitrate     bool          `json:"enablestringerbitrate"`
	Insert_sps_pps            bool          `json:"insert_sps_pps"`
	Num_b_frames              uint          `json:"num_b_frames"`
	Slice_header_spacing      uint32        `json:"slice_header_spacing"`
	Profile                   int           `json:"profile"`
	Insert_aud                bool          `json:"insert_aud"`
	Insert_vui                bool          `json:"insert_vui"`
	Cabac_entropy_coding      bool          `json:"cabac_entropy_coding"`
	Video_xraw_h264           videoXrawH264 `json:"video_xraw_h264"`
}

type rtspclientsink struct {
	Name                 string `json:"name"`
	Parent               string `json:"parent"`
	Async_handling       bool   `json:"async_handling"`
	Message_forward      bool   `json:"message_forward"`
	Location             string `json:"location"`
	Protocols            int    `json:"protocols"`
	Debug                bool   `json:"debug"`
	Retry                uint   `json:"retry"`
	Timeout              uint64 `json:"timeout"`
	Tcp_timeout          uint64 `json:"tcp_timeout"`
	Latency              uint   `json:"latency"`
	Rtx_time             uint   `json:"rtx_time"`
	Do_rtsp_keep_alive   bool   `json:"do_rtsp_keep_alive"`
	Proxy                string `json:"proxy"`
	Proxy_id             string `json:"proxy_id"`
	Proxy_pw             string `json:"proxy_pw"`
	Rtp_blocksize        uint   `json:"rtp_blocksize"`
	User_id              string `json:"user_id"`
	User_pw              string `json:"user_pw"`
	Port_range           string `json:"port_range"`
	Udp_buffer_size      int    `json:"udp_buffer_size"`
	Udp_reconnect        bool   `json:"udp_reconnect"`
	Multicast_iface      string `json:"multicast_iface"`
	Sdes                 string `json:"sdes"`
	Tls_validation_flags int    `json:"tls_validation_flags"`
	Tls_database         string `json:"tls_database"`
	Tls_interaction      string `json:"tls_interaction"`
	Ntp_time_source      int    `json:"ntp_time_source"`
	User_agent           string `json:"user_agent"`
	Profiles             int    `json:"profiles"`
}

type cameraControl struct {
	Nvarguscamerasrc nvarguscamerasrc `json:"nvarguscamerasrc"`
	Nvvidconv        nvvidconv        `json:"nvvidconv"`
	Omxh264enc       omxh264enc       `json:"omxh264enc"`
	Rtspclientsink   rtspclientsink   `json:"rtspclientsink"`
}

var _videoXrawMemoryNvarguscamerasrc = videoXrawMemory{
	Width:     3280,
	Height:    2464,
	Framerate: 21,
	Format:    "NV12",
}

var _nvarguscamerasrcData = nvarguscamerasrc{
	Name: "nvarguscamerasrc1", Blocksize: 4096,
	Num_buffers:          -1,
	Typefind:             false,
	Do_timestamp:         true,
	Silent:               true,
	Timeout:              0,
	Wbmode:               1,
	Saturation:           1,
	Sensor_id:            0,
	Sensor_mode:          -1,
	Total_sensor_modes:   0,
	Exposuretimerange:    "",
	Gainrange:            "",
	Ispdigitalgainrange:  "",
	Tnr_strength:         -1,
	Tnr_mode:             1,
	Ee_mode:              1,
	Ee_strength:          -1,
	Aeantibanding:        1,
	Exposurecompensation: 0,
	Aelock:               false,
	Aeregion:             "",
	Awblock:              false,
	Video_xraw_memory:    _videoXrawMemoryNvarguscamerasrc,
}
var _videoxrawNvvidconv = videoXraw{
	Width:     816,
	Height:    616,
	Framerate: 21,
	Format:    "NV12",
}

var _nvvidconvData = nvvidconv{
	Name:                 "nvvidconv0",
	Parent:               "",
	Qos:                  false,
	Silent:               false,
	Flip_method:          2,
	Output_buffers:       4,
	Interpolation_method: 0,
	Left:                 0,
	Right:                0,
	Top:                  0,
	Bottom:               0,
	B1_output:            true,
	Video_xraw:           _videoxrawNvvidconv,
}
var _videoXrawH264Omxh264enc = videoXrawH264{
	Width:         816,
	Height:        616,
	Stream_format: "byte-stream",
}
var _omxh264encData = omxh264enc{
	Name:                      "omxh264enc-omxh264enc0",
	Parent:                    "",
	Qos:                       false,
	Control_rate:              1,
	Bitrate:                   4000000,
	Peak_bitrate:              0,
	Quant_i_frames:            4294967295,
	Quant_p_frames:            4294967295,
	Quant_b_frames:            4294967295,
	Iframeinterval:            0,
	Sliceintrarefreshenable:   false,
	Sliceintrarefreshinterval: 60,
	Bit_packetization:         false,
	Vbv_size:                  10,
	Temporal_tradeoff:         0,
	Enablemvbuffermeta:        false,
	Qp_range:                  "-1,-1:-1,-1:-1,-1",
	Measureencoderlatency:     false,
	Enabletwopasscbr:          false,
	Preset_level:              0,
	Enablestringerbitrate:     false,
	Insert_sps_pps:            false,
	Num_b_frames:              0,
	Slice_header_spacing:      0,
	Profile:                   1,
	Insert_aud:                false,
	Insert_vui:                false,
	Cabac_entropy_coding:      false,
	Video_xraw_h264:           _videoXrawH264Omxh264enc,
}
var _rtspclientsinkData = rtspclientsink{
	Name:                 "rtspclientsink0",
	Parent:               "",
	Async_handling:       false,
	Message_forward:      false,
	Location:             "rtsp://localhost:8554/mystream",
	Protocols:            7,
	Debug:                false,
	Retry:                20,
	Timeout:              5000000,
	Tcp_timeout:          5000000,
	Latency:              2000,
	Rtx_time:             500,
	Do_rtsp_keep_alive:   true,
	Proxy:                "",
	Proxy_id:             "",
	Proxy_pw:             "",
	Rtp_blocksize:        0,
	User_id:              "",
	User_pw:              "",
	Port_range:           "",
	Udp_buffer_size:      524288,
	Udp_reconnect:        true,
	Multicast_iface:      "",
	Sdes:                 "",
	Tls_validation_flags: 127,
	Tls_interaction:      "",
	Ntp_time_source:      0,
	User_agent:           "GStreamer/1.14.5",
	Profiles:             1,
}
var _cameraControlData = cameraControl{
	Nvarguscamerasrc: _nvarguscamerasrcData,
	Nvvidconv:        _nvvidconvData,
	Omxh264enc:       _omxh264encData,
	Rtspclientsink:   _rtspclientsinkData,
}

func getTodos(context *gin.Context) {
	context.IndentedJSON(http.StatusOK, _cameraControlData)
}

func addToDo(context *gin.Context) {
	var newData cameraControl

	if err := context.BindJSON(&newData); err != nil {
		return
	}

	_cameraControlData = newData
	content, err := json.Marshal(_cameraControlData)
	if err != nil {
		fmt.Println(err)
	}
	context.IndentedJSON(http.StatusCreated, _cameraControlData)
	err = ioutil.WriteFile("/home/dotai/gst_camera/test.json", content, 0644)
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	router := gin.Default()
	router.GET("/cameraControl", getTodos)
	router.POST("/cameraControl", addToDo)
	router.Run("192.168.0.146:9090")
}
