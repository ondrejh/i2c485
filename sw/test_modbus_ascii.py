from serial import Serial

def byteToHexAscii(byte):

    ''' function converting single byte value (0..255) to hex ascii string
    arguments: byte .. value
    return: string '''

    return '{:02X}'.format(byte)

def composeModbusAsciiFrame(address,function,data):
    
    ''' fuction composing Modbus ASCII frame
    arguments: address .. address value (0..255)
               function .. function value (0..255)
               data .. bytes
    return: ascii bytes representation of modbus ASCII message frame '''
    
    frame = ':'

    frame += (byteToHexAscii(address))  #address
    frame += (byteToHexAscii(function)) #function

    lrc = address+function

    for b in data:                      #data
        frame += (byteToHexAscii(b))
        lrc += b

    lrc = (0xFF-lrc+1)%0x100            #lrc
    frame += (byteToHexAscii(lrc))

    frame += '\r\n'

    return bytes(frame,'ascii')

def decomposeModbusAsciiFrame(frame):

    address     = b'00'
    function    = b'00'
    data        = b''
    lrc         = b'00'
    error       = 0

    try:
        fcore = frame[(frame.find(b':')+1):(frame.find(b'\r'))]
        address = fcore[0:2]
        function = fcore[2:4]
        data = fcore[4:-2]
        lrc = fcore[-2:]
    except:
        error = -1 #message disassembling error

    try:
        address = int(address.decode('ascii'),16)
        function = int(function.decode('ascii'),16)
        dout = b''
        while len(data)>0:
            byte = int(data[0:2].decode('ascii'),16)
            data = data[2:]
            dout += bytes([byte])
        data = dout
        lrc = int(lrc.decode('ascii'),16)
    except:
        error = -2 #message decode error

    lrc_check = address+function
    for byte in data:
        lrc_check+=byte
    lrc_check = (0xFF-lrc_check+1)%0x100
    if lrc_check!=lrc:
        error = -3 #lrc error

    return (error,address,function,data,lrc)

if __name__ == "__main__":

    from time import sleep

    with Serial('COM19',19200,bytesize=7,parity='E',timeout=0.1) as port:

        message = composeModbusAsciiFrame(123,234,b'ahoj')

        while(True):
            print(port.readlines())
            for b in message:
                print('{:02X} '.format(b),end='')
            print('')
            print(decomposeModbusAsciiFrame(message))
            port.write(message)
            sleep(1)
    
