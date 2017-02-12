#ifndef INC_AWS_IOT_CONFIG_H
#define INC_AWS_IOT_CONFIG_H

// trusted root CA certificate
const char * get_trusted_root_ca_certificate();

// AWS IoT client endpoint
const char * get_aws_iot_client_endpoint();

// AWS IoT device certificate (ECC)
const char * get_aws_iot_device_certificate();

// AWS IoT device private key (ECC)
const char * get_aws_iot_device_private_key();

#endif
