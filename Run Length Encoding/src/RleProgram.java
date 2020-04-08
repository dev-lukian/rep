import java.util.ArrayList;
import java.util.Scanner;

public class RleProgram extends ConsoleGfx {

    // Ex: toHexString(new byte[] { 3, 15, 6, 4 }) yields string "3f64".
    public static String toHexString(byte[] data) {
        String hexString = "";

        for (byte element : data) {
            hexString += Integer.toHexString(element);
        }

        return hexString;
    }

    // Ex: countRuns(new byte[] { 15, 15, 15, 4, 4, 4, 4, 4, 4 }) yields integer 2.
    public static int countRuns(byte[] flatData) {
        int countRuns;
        if (flatData.length == 0 || flatData == null) {
            countRuns = 0;
            return countRuns;
        }
        else {
            countRuns = 1;
        }

        int storedRun = flatData[0];
        int countNum = 0;

        for (byte element : flatData) {
            if (element == storedRun) {
                ++countNum;
                if (countNum == 15) {
                    ++countRuns;
                    countNum = 0;
                }
            }
            else {
                ++countRuns;
                storedRun = element;
                countNum = 0;
            }
        }

        return countRuns;
    }

    // Ex: encodeRle(new byte[] { 15, 15, 15, 4, 4, 4, 4, 4, 4 }) yields byte array { 3, 15, 6, 4 }.
    public static byte[] encodeRle(byte[] flatData) {
        byte[] byteArray = new byte[countRuns(flatData)*2];
        byte target = flatData[0];
        byte count = 0;
        int index = 0;

        for (int i = 0; i < flatData.length; ++i) {
            if (flatData[i] == target) {
                if (count == 15) {
                    byteArray[index] = count;
                    byteArray[index + 1] = target;
                    index += 2;
                    count = 1;
                    target = flatData[i];
                }
                else {
                    ++count;
                    target = flatData[i];
                }
            }
            else {
                byteArray[index] = count;
                byteArray[index + 1] = target;
                index += 2;
                count = 1;
                target = flatData[i];
            }

            if (i == (flatData.length - 1)) {
                byteArray[index] = count;
                byteArray[index + 1] = target;
            }

        }

        return byteArray;
    }

    // Ex: getDecodedLength(new byte[] { 3, 15, 6, 4 }) yields integer 9.
    public static int getDecodedLength(byte[] rleData) {
        int countTotal = 0;

        for (int i = 0; i < rleData.length; i += 2) {
            countTotal += rleData[i];
        }

        return countTotal;
    }

    // Ex: decodeRle(new byte[] { 3, 15, 6, 4 }) yields byte array { 15, 15, 15, 4, 4, 4, 4, 4, 4 }.
    public static byte[] decodeRle(byte[] rleData) {
        byte[] byteArray = new byte[getDecodedLength(rleData)];
        int index = 0;

        for (int i = 0; i < rleData.length; i += 2) {
            for (int j = 0; j < rleData[i]; ++j) {
                byteArray[index] = rleData [i + 1];
                ++index;
            }
        }

        return byteArray;
    }

    // Ex: stringToData ("3f64") yields byte array { 3, 15, 6, 4 }.
    public static byte[] stringToData(String dataString) {
        ArrayList<Byte> decimalConversion = new ArrayList<>();
        int decimal;

        for (int i = 0; i < dataString.length(); ++i) {
            decimal = Character.getNumericValue(dataString.charAt(i));
            decimalConversion.add((byte) decimal);
        }

        byte[] byteArray = new byte[decimalConversion.size()];

        for(int i = 0; i < byteArray.length; ++i) {
            byteArray[i] = decimalConversion.get(i);
        }

        return byteArray;
    }

    // Ex: toRleString(new byte[] { 15, 15, 6, 4 }) yields string "15f:64".
    public static String toRleString(byte[] rleData) {
        String rleString = "";
        String decimal;
        String hexadecimal;


        for (int i = 0; i < rleData.length; i += 2) {
            decimal = Integer.toString(rleData[i]);
            hexadecimal = Integer.toHexString(rleData[i + 1]);
            if (i == (rleData.length - 2)) {
                rleString += decimal + hexadecimal;
            }
            else {
                rleString += decimal + hexadecimal + ":";
            }
        }

        return rleString;
    }

    // Ex: stringToRle("15f:64") yields byte array { 15, 15, 6, 4 }.
    public static byte[] stringToRle(String rleString) {
        String[] splitArray = rleString.split(":");
        ArrayList<Byte> decimalConversion = new ArrayList<>();

        for (int i = 0; i < splitArray.length; ++i) {
            if (splitArray[i].length() == 2) {
                decimalConversion.add((byte) Character.getNumericValue(splitArray[i].charAt(0)));
                decimalConversion.add((byte) Character.getNumericValue(splitArray[i].charAt(1)));
            }
            else if (splitArray[i].length() == 3){
                decimalConversion.add((byte) Integer.parseInt(splitArray[i].substring(0,2)));
                decimalConversion.add((byte) Character.getNumericValue(splitArray[i].charAt(2)));
            }
        }

        // Converting from ArrayList to an Array
        byte[] byteArray = new byte[decimalConversion.size()];

        for(int i = 0; i < byteArray.length; ++i) {
            byteArray[i] = decimalConversion.get(i);
        }

        return byteArray;
    }

    public static void main(String[] args) {
        int userOption; // 0-9
        byte[] currentFile = null; // Holds current image that can be displayed
        String fileName;
        String rleHexString;
        String rleString;
        String flatHexString;
        boolean menu = true;

        Scanner scnr = new Scanner(System.in);

        System.out.println("Welcome to the RLE image encoder!\n\nDisplaying Spectrum Image:");
        ConsoleGfx.displayImage(ConsoleGfx.testRainbow);

        while (menu) {
            // User Menu
            System.out.println("\nRLE Menu\n" +
                    "--------\n" +
                    "0. Exit\n" +
                    "1. Load File\n" +
                    "2. Load Test Image\n" +
                    "3. Read RLE String\n" +
                    "4. Read RLE Hex String\n" +
                    "5. Read Data Hex String\n" +
                    "6. Display Image\n" +
                    "7. Display RLE String\n" +
                    "8. Display Hex RLE Data\n" +
                    "9. Display Hex Flat Data\n");
            System.out.print("Select a Menu Option: ");
            userOption = scnr.nextInt();

            // Limits user to select options only from given menu (0-9)
            if (userOption < 0 || userOption > 9) {
                System.out.println("Error! Invalid input.");

            }

            switch (userOption) {
                // Exit
                case 0:
                    menu = false;
                    break;
                // Load File
                case 1:
                    System.out.print("Enter name of file to load: ");
                    fileName = scnr.next();
                    currentFile = ConsoleGfx.loadFile(fileName);
                    break;
                // Load Test Image
                case 2:
                    currentFile = ConsoleGfx.testImage;
                    System.out.println("Test image data loaded.");
                    break;
                // Loads RLE String ("15f:64")
                case 3:
                    System.out.print("Enter an RLE string to be decoded: ");
                    rleString = scnr.next();
                    currentFile = decodeRle(stringToRle(rleString));
                    break;
                // Loads RLE Hex String
                case 4:
                    System.out.print("Enter the hex string holding RLE data: ");
                    rleHexString = scnr.next();
                    currentFile = decodeRle(stringToData(rleHexString));
                    break;
                // Loads Data Hex String
                case 5:
                    System.out.print("Enter the hex string holding flat data: ");
                    flatHexString = scnr.next();
                    currentFile = stringToData(flatHexString);
                    break;
                // Displays Image
                case 6:
                    System.out.print("Displaying image...\n");
                    if (currentFile == null) {
                        System.out.print("(no data)\n");
                        break;
                    }
                    ConsoleGfx.displayImage(currentFile);
                    break;
                // Displays RLE String
                case 7:
                    System.out.print("RLE representation: ");
                    if (currentFile == null) {
                        System.out.print("(no data)\n");
                        break;
                    }
                    System.out.print(toRleString(encodeRle(currentFile))+"\n");
                    break;
                // Displays Hex RLE Data
                case 8:
                    System.out.print("RLE hex values: ");
                    if (currentFile == null) {
                        System.out.print("(no data)\n");
                        break;
                    }
                    System.out.print(toHexString(encodeRle(currentFile))+"\n");
                    break;
                // Displays Hex Flat Data
                case 9:
                    System.out.print("Flat hex values: ");
                    if (currentFile == null) {
                        System.out.print("(no data)\n");
                        break;
                    }
                    System.out.print(toHexString(currentFile)+"\n");
                    break;
            }

        }
    }
}
