use std::fs;


/**
 * first 3 bits are the packet version
 * next 3 are the packet ID type
 *  ID 4 == literal value, broken up into 5 bit segments, most significant is whether there are additional segements (1XXXX)
    *  concatenate groups for the value
    *  there may be "leftover" 0 bits
 *  ID NOT 4 represents an operator and sub packets
 *      can contain 1-M subpackets
 *      next 1 bit is whether:
 *          1 = 15bits for packet bit length (many subpackets within)
 *          0 = 11bits for # of sub packets
 *      operator packets can infinitely nest, literals cannot
 * 
 * 0011100000000000011011
 * VVVTTTILLLLLLLLLLLLLLL
 * Version 1, Type 6, 15bit packet length, length of 27 bits
 * 
 * 11010001010
 * VVVTTTAAAAA
 * Version 6
 * Type 4
 * Literal 10
 * 
 * 0101001000100100
 * VVVTTTBBBBBBBBBB
 * Version 2, Type 4, 00010100 = Literal 20
 * 
 * approach:
 *  packet type/enums
 * 
 * 
 * 
 */

type PacketSize = u16;
const HEADER_SIZE: PacketSize = 6;

 #[derive(Debug)]
enum PacketType {
    Operator(OperatorType),
    Literal,
}

#[derive(Debug)]
enum OperatorType {
    Bits(PacketSize),
    Count(PacketSize),
    Unknown
}

#[derive(Debug)]
struct Packet {
    version: u8,
    id: PacketType,
    value: u64,
    pub len: PacketSize,
    nested: Vec<Packet>
}

impl Packet {
    pub fn new(bits: &str) -> Packet {
        let (version, id) = Packet::parse_header(bits);
        let mut packet = Packet { version, id, value: 0, nested: Vec::new(), len: 0 };
        let bytes_parsed = packet.parse(&bits[6..]);
        packet.len += bytes_parsed + HEADER_SIZE;
        packet
    }

    fn parse_header(bits: &str) -> (u8, PacketType) {
        assert!(bits.len() >= 6, "bits not long enough for header {bits}");
        println!("header bits {}", &bits);
        let version = u8::from_str_radix(&bits[0..3], 2).unwrap();
        let id_bits = u8::from_str_radix(&bits[3..6], 2).unwrap();
        let id: PacketType;
        if id_bits == 4 {
            id = PacketType::Literal;
        } else {
            id = PacketType::Operator(OperatorType::Unknown);
        }
        (version, id)
    }

    pub fn parse(&mut self, bits: &str) -> PacketSize {
        match self.id {
            PacketType::Literal => self.parse_literal(bits),
            PacketType::Operator(_) => self.parse_operator(bits),
        }
    }

    fn parse_literal(&mut self, bits: &str) -> PacketSize {
        let mut offset: PacketSize = 0;
        let mut parsed = String::new();
        
        let mut chunk = &bits[offset.into()..(offset+5).into()];
        while &chunk[..1] == "1" {
            println!("chunk: {}", chunk);
            parsed += &chunk[1..];
            offset += 5;
            if bits.len() <= offset.into() {
                break;
            }
            chunk = &bits[offset.into()..(offset+5).into()];
        } 
        // parse last chunk
        parsed += &chunk[1..];
        offset += 5;
        self.value = u64::from_str_radix(&parsed, 2).unwrap();
        offset
    }

    /** 
     * Built for Operator Type packets, a way to tell if they've been read fully agnostic
     * of packet type
     */
    fn read_total(&self, offset: PacketSize, packets_read: PacketSize) -> bool {
        match self.id {
            PacketType::Operator(OperatorType::Bits(bits)) => {
                offset >= bits
            }
            PacketType::Operator(OperatorType::Count(total)) => {
                packets_read >= total
            }
            _ => { false }
        }
    }

    fn parse_operator(&mut self, bits: &str) -> PacketSize {
        let size_bit = &bits[..1];
        if size_bit == "1" {
            // 11 bits for the number of packets to read in
            let count = PacketSize::from_str_radix(&bits[1..12], 2).unwrap();
            self.id = PacketType::Operator(OperatorType::Count(count));
            self.parse_nested(&bits[12..]) + 12
        } else {
            let total = PacketSize::from_str_radix(&bits[1..16], 2).unwrap();
            self.id = PacketType::Operator(OperatorType::Bits(total));
            self.parse_nested(&bits[16..]) + 16
            // 15 bits for the length of bits to read in
        }
    }

    /**
     * Parses nested packets with a bit count limit
     */
    fn parse_nested(&mut self, bits: &str) -> PacketSize {
        let mut offset: PacketSize = 0;
        let mut packets_read: PacketSize = 0;
        dbg!(&self);
        while !self.read_total(offset, packets_read) {
            let packet = Packet::new(&bits[offset.into()..]);
            offset += packet.len;
            packets_read += 1;
            dbg!(&packet);
            self.nested.push(packet);
        }
        offset
    }
}

fn sum_version(packet: &Packet) -> u32 {
    let mut sum = 0;
    if packet.nested.len() > 0 {
        for nested_packet in packet.nested.iter() {
            sum += sum_version(nested_packet);
        }
    }
    let version: u32 = packet.version.into();
    sum + version
}

fn hex_to_binary(hex: &String) -> String {
    let mut binary = String::new();
    assert!(hex.is_ascii());
    for char in hex.chars() {
        let single_bin = match char {
            '0' => "0000",
            '1' => "0001",
            '2' => "0010",
            '3' => "0011",
            '4' => "0100",
            '5' => "0101",
            '6' => "0110",
            '7' => "0111",
            '8' => "1000",
            '9' => "1001",
            'A' => "1010",
            'B' => "1011",
            'C' => "1100",
            'D' => "1101",
            'E' => "1110",
            'F' => "1111",
            _ => ""
        };
        binary.push_str(single_bin);
    }
    binary
}


fn main() {
    // read in file
    let hexadecimal = fs::read_to_string("./puzzle.txt")
        .expect("Error reading file");
    let bits = hex_to_binary(&hexadecimal);
    println!("{}", bits);

    let packet = Packet::new(&bits);
    println!("{:?}",packet);
    println!("{}", sum_version(&packet));
}
