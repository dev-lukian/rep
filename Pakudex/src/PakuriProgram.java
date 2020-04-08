import java.util.Scanner;

// Test
public class PakuriProgram {
    public static void main(String args[]) {
        int pakudexCapacity;
        int userOption;
        String pakuriName;
        boolean menu = true; //Set to true to have menu keep looping until user exits (option 6)

        Scanner scnr = new Scanner(System.in);

        System.out.println("Welcome to Pakudex: Tracker Extraordinaire!");
        // Loops system request for a max capacity until a valid size is entered.
        while (true) {
            System.out.print("Enter max capacity of the Pakudex: ");
            try {
                String x = scnr.next();
                pakudexCapacity = Integer.parseInt(x);
                // Negative number is not a valid size
                if (pakudexCapacity < 0) {
                    System.out.println("Please enter a valid size.");
                    continue;
                }
                break;
            // String input is not a valid size as well
            } catch (Exception e) {
                System.out.println("Please enter a valid size.");
            }
        }

        // Constructs new Pakudex object with capacity of pakudexCapacity
        Pakudex userPakudex = new Pakudex(pakudexCapacity);
        System.out.println("The Pakudex can hold " + pakudexCapacity + " species of Pakuri.");

        while (menu) {

            while (true) {
                // Main menu
                System.out.println("\nPakudex Main Menu" +
                        "\n-----------------" +
                        "\n1. List Pakuri" +
                        "\n2. Show Pakuri" +
                        "\n3. Add Pakuri" +
                        "\n4. Evolve Pakuri" +
                        "\n5. Sort Pakuri" +
                        "\n6. Exit");

                System.out.print("\nWhat would you like to do? ");


                try {
                    String x = scnr.next();
                    userOption = Integer.parseInt(x);
                    // Restricts user to stay within the bounds of [1, 6]
                    if (userOption > 6 || userOption < 1) {
                        System.out.println("Unrecognized menu selection!");
                        continue;
                    }
                    break;
                // String is invalid input for menu selection
                } catch (Exception e) {
                    System.out.println("Unrecognized menu selection!");
                }
            }

            // List Pakuri
            if (userOption == 1) {
                listPakuri(userPakudex);
            }

            // Show Pakuri (stats)
            else if (userOption == 2) {
                System.out.print("Enter the name of the species to display: ");
                pakuriName = scnr.next();
                if (userPakudex.getStats(pakuriName) == null) {
                    System.out.println("Error: No such Pakuri!");
                }
                else {
                    userPakudex.printStats(pakuriName);
                }
            }

            // Add Pakuri
            else if (userOption == 3) {
                // If size of Pakuri array is equal to its capacity, then it is full. No more pakuri can be added
                if (userPakudex.getSize() == userPakudex.getCapacity()) {
                    System.out.println("Error: Pakudex is full!");
                    continue;
                }

                System.out.print("Enter the name of the species to add: ");
                pakuriName = scnr.next();
                // True case
                if (userPakudex.addPakuri(pakuriName)) {
                    System.out.println("Pakuri species " + pakuriName + " successfully added!");
                }
                // False case (duplicate error)
                else {
                    System.out.println("Error: Pakudex already contains this species!");
                }
            }

            // Evolve Pakuri
            else if (userOption == 4) {
                System.out.print("Enter the name of the species to evolve: ");
                pakuriName = scnr.next();
                if (userPakudex.evolveSpecies(pakuriName)) {
                    System.out.println(pakuriName + " has evolved!");
                }
                else {
                    System.out.println("Error: No such Pakuri!");
                }
            }

            // Sort
            else if (userOption == 5) {
                userPakudex.sortPakuri();
                System.out.println("Pakuri have been sorted!");
            }

            // Exit Program
            else if (userOption == 6) {
                System.out.println("Thanks for using Pakudex! Bye!");
                menu = false;
            }
        }
    }

    public static void listPakuri(Pakudex pakudex) {
        if (pakudex.getSpeciesArray() == null) {
            System.out.println("No Pakuri in Pakudex yet!");
        }
        else {
            System.out.println("Pakuri In Pakudex:");
            for (int i = 0; i < pakudex.getSpeciesArray().length; ++i) {
                System.out.println(i + 1 + ". " + pakudex.getSpeciesArray()[i]);
            }
        }
    }
}
