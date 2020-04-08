import java.util.Arrays; // used for Array.fill & Arrays.deepToString
import java.util.Scanner;


public class ConnectFour {

    // Method that prints out board
    public static void printBoard(char[][] array) {
        // Prints board with index 0 being at the bottom
        for (int row = array.length - 1; row >= 0; --row) {
            for (int col = 0; col < array[row].length; ++col) {
                System.out.print(array[row][col] + " ");
            }
            System.out.println(); // New line after each row
        }
    }

    // Sets each element of the board to a dash at the very beginning of the game
    public static void initializeBoard(char[][] array) {
        for (char[] row : array) {
            Arrays.fill(row, '-');
        }
    }

    // Inserts a chip based off the col index user picks
    public static int insertChip(char[][] array, int col, char chipType) {
        int chipRow = -1;

        for (int row = 0; row < array.length ; ++row) {
            if (array[row][col] == '-') {
                array[row][col] = chipType;
                chipRow = row;
                break;
            }
        }

        return chipRow;
    }

    public static boolean checkIfWinner(char[][] array, int col, int row, char chipType) {
        boolean win = false;
        String horizontalCheck = "";
        String verticalCheck = "";
        String chipString = Character.toString(chipType); // Converts chipType from character to String
        String fourChips = chipString + chipString + chipString + chipString; // "oooo" or "xxxx" depending on chipType

        for (int i = 0; i < array[row].length; ++i) {
            horizontalCheck += Character.toString(array[row][i]);
        }
        if (horizontalCheck.contains(fourChips)) {
            win = true;
        }

        for (int i = 0; i < array.length; ++i) {
            verticalCheck += Character.toString(array[i][col]);
        }
        if (verticalCheck.contains(fourChips)) {
            win = true;
        }

        return win;
    }

    public static boolean checkIfTie(char[][] array) {
        boolean tie = false;

        // If array does not contain any dashes, the board is filled up with 'x' & 'o'
        if (!Arrays.deepToString(array).contains("-")) {
            tie = true;
        }

        return tie;
    }

    public static void main (String[] args) {
        Scanner scnr = new Scanner(System.in);
        int boardHeight;
        int boardLength;
        int playerXCol;
        int playerXRow;
        int playerOCol;
        int playerORow;
        boolean checkIfWinner = false; // Set to false to keep running the while loop until someone wins

        System.out.print("What would you like the height of the board to be? ");
        boardHeight = scnr.nextInt();
        System.out.print("What would you like the length of the board to be? ");
        boardLength = scnr.nextInt();

        // Initializes new Connect Four board based off the dimensions user inputs
        char[][] connectFour = new char[boardHeight][boardLength];

        initializeBoard(connectFour);
        printBoard(connectFour);

        System.out.println("\nPlayer 1: x\nPlayer 2: o");

        while (!checkIfWinner) {
            // Player 1 Turn
            System.out.print("\nPlayer 1: Which column would you like to choose? ");
            playerXCol = scnr.nextInt();
            playerXRow = insertChip(connectFour, playerXCol, 'x');
            printBoard(connectFour);
            if (checkIfTie(connectFour)) {
                System.out.println("\nDraw. Nobody wins.");
                break;
            }
            checkIfWinner = checkIfWinner(connectFour, playerXCol, playerXRow, 'x');
            if (checkIfWinner) {
                System.out.println("\nPlayer 1 won the game!");
                continue;
            }

            // Player 2 Turn
            System.out.print("\nPlayer 2: Which column would you like to choose? ");
            playerOCol = scnr.nextInt();
            playerORow = insertChip(connectFour, playerOCol, 'o');
            printBoard(connectFour);
            if (checkIfTie(connectFour)) {
                System.out.println("\nDraw. Nobody wins.");
                break;
            }
            checkIfWinner = checkIfWinner(connectFour, playerOCol, playerORow, 'o');
            if (checkIfWinner) {
                System.out.println("\nPlayer 2 won the game!");
                continue;
            }
        }
    }
}
