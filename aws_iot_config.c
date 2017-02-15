#include "aws_iot_config.h"

// trusted root CA certificate - https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
const char *__ca_cert = "-----BEGIN CERTIFICATE-----\r\n"
        "MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\r\n"
        "yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\r\n"
        "ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\r\n"
        "U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\r\n"
        "ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\r\n"
        "aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\r\n"
        "MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\r\n"
        "ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\r\n"
        "biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\r\n"
        "U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\r\n"
        "aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\r\n"
        "nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\r\n"
        "t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\r\n"
        "SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\r\n"
        "BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\r\n"
        "rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\r\n"
        "NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\r\n"
        "BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\r\n"
        "BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\r\n"
        "aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\r\n"
        "MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\r\n"
        "p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\r\n"
        "5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\r\n"
        "WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\r\n"
        "4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\r\n"
        "hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\r\n"
        "-----END CERTIFICATE-----\r\n";

// AWS IoT client endpoint
//const char *client_endpoint = "<your-prefix>.iot.<aws-region>.amazonaws.com";
const char *__client_endpoint = "a3hg6mct54rala.iot.us-west-2.amazonaws.com";

// AWS IoT device certificate (ECC)
const char *__client_cert =
"-----BEGIN CERTIFICATE-----\r\n"
"MIIC5jCCAc6gAwIBAgIVAOHk8aO9tG7OxgUnxjVFLeFX8GNXMA0GCSqGSIb3DQEB\r\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\r\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xNjEyMjExMDUw\r\n"
"NTFaFw00OTEyMzEyMzU5NTlaMHUxCzAJBgNVBAYTAklOMRIwEAYDVQQIDAlLYXJu\r\n"
"YXRha2ExEjAQBgNVBAcMCUJlbmdhbHVydTEMMAoGA1UECgwDRVNQMQ4wDAYDVQQD\r\n"
"DAVtYWtlcjEgMB4GCSqGSIb3DQEJARYRaGluZ29sZUB5YWhvby5jb20wWTATBgcq\r\n"
"hkjOPQIBBggqhkjOPQMBBwNCAATW+qd/YFO6oD9DBbq5FEm0YuwHiXuWjv14h1rL\r\n"
"+fTDoHw+EbXZTyKqN/HXOfaU3M28vrULyqoc1Rnv71ulvGpNo2AwXjAfBgNVHSME\r\n"
"GDAWgBTubCYgCE+XGh0C2EMI+Dtjo6l3GzAdBgNVHQ4EFgQUtvMFTckCZVSz7uC3\r\n"
"yS9Bnq1j2xUwDAYDVR0TAQH/BAIwADAOBgNVHQ8BAf8EBAMCB4AwDQYJKoZIhvcN\r\n"
"AQELBQADggEBABcJ3w02wVUmy3ISIKk53j87/cm87jFATD4GNm+doVJ3XFLYWyzz\r\n"
"9HPgWMvu2OEXp3JQs0/dM81pc9X7G0N1JR+5f4CTwlQ9FQ6fjQTSR2hhll230S8N\r\n"
"ITmGH0PJY/yAbRFcOGUZmL+t52a+PJ00fkq5akcI5imcM2ri/gbwId6+S8H9YC+m\r\n"
"7vJzQEXtNLzVdTFDlmc0v8ps7OfvX81CiVo8XpzFbWJcbrU49QmYqZ8dG/diFkHF\r\n"
"dSvWk6HCfOE65u4+M5TCtwZLIfperoVNux+xRw6+kcMjWJ7HZd+aFNqb4Bl+dnu0\r\n"
"oPXa04+D4HUwbHHzQrXa4Kfx6CeLRZuDTJM=\r\n"
"-----END CERTIFICATE-----\r\n";

// AWS IoT device private key (ECC)
const char *__client_key =
"-----BEGIN EC PARAMETERS-----\r\n"
"BggqhkjOPQMBBw==\r\n"
"-----END EC PARAMETERS-----\r\n"
"-----BEGIN EC PRIVATE KEY-----\r\n"
"MHcCAQEEIBbWFdp73fSJhOMSKLPi3/DTvPjmya++WjSiGQZRoj5foAoGCCqGSM49\r\n"
"AwEHoUQDQgAE1vqnf2BTuqA/QwW6uRRJtGLsB4l7lo79eIday/n0w6B8PhG12U8i\r\n"
"qjfx1zn2lNzNvL61C8qqHNUZ7+9bpbxqTQ==\r\n"
"-----END EC PRIVATE KEY-----\r\n";

// trusted root CA certificate
const char * get_trusted_root_ca_certificate() {
  return __ca_cert;
}

// AWS IoT client endpoint
const char * get_aws_iot_client_endpoint() {
  return __client_endpoint;
}

// AWS IoT device certificate (ECC)
const char * get_aws_iot_device_certificate() {
  return __client_cert;
}

// AWS IoT device private key (ECC)
const char * get_aws_iot_device_private_key() {
  return __client_key;
}
