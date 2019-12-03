public class Pakudex {
    private Pakuri[] pakudex;

    // Default constructor
    public Pakudex() {
        pakudex = new Pakuri[20];
    }
    // Overloaded constructor
    public Pakudex(int capacity) {
        pakudex = new Pakuri[capacity];
    }

    public int getSize() {
        int count = 0;

        for (Pakuri element : pakudex) {
            if (element != null) {
                count += 1;
            }
        }

        return count;
    }

    public int getCapacity() {
        return pakudex.length;
    }

    public String[] getSpeciesArray() {
        // Returns null right away if all elements are null
        if (getSize() == 0) {
            return null;
        }

        // Initializes string array based on size
        String[] speciesList = new String[getSize()];
        int i = 0;

        for (Pakuri pakuri : pakudex) {
            if (pakuri != null) {
                speciesList[i] = pakuri.getSpecies();
                ++i;
            }
        }

        return speciesList;
    }

    public int[] getStats(String species) {
        if (findPakuri(species) == -1) {
            return null;
        }

        // [attack, defense, speed]
        int[] stats = new int[3];

        for (int i = 0; i < getSize(); ++i) {
            if (pakudex[i].getSpecies().equals(species)) {
                stats[0] = pakudex[i].getAttack();
                stats[1] = pakudex[i].getDefense();
                stats[2] = pakudex[i].getSpeed();
                break;
            }
        }

        return stats;
    }

    public void printStats(String species) {
        int[] stats = getStats(species);

        System.out.println("\nSpecies: " + species);
        System.out.println("Attack: " + stats[0]);
        System.out.println("Defense: " + stats[1]);
        System.out.println("Speed: " + stats[2]);
    }

    public void sortPakuri() {
        Pakuri temp;

        // Bubble sort
        for (int i = 0; i < getSize(); ++i) {
            for (int j = i + 1; j < getSize(); ++j) {
                if (pakudex[j].getSpecies().compareTo(pakudex[i].getSpecies()) < 0) {
                    temp = pakudex[i];
                    pakudex[i] = pakudex[j];
                    pakudex[j] = temp;
                }
            }
        }
    }

    public boolean addPakuri(String species) {
        for (int i = 0; i < pakudex.length; ++i) {
            // Checks to see if object is null first, to refrain from nullPointerException error
            if (pakudex[i] == null) {
                pakudex[i] = new Pakuri(species);
                return true;
            }
            else if (pakudex[i].getSpecies().equals(species)) {
                return false;
            }
        }

        return false;
    }

    public boolean evolveSpecies(String species) {
        for (int i = 0; i < getSize(); ++i) {
            if (pakudex[i].getSpecies().equals(species)) {
                pakudex[i].evolve();
                return true;
            }
        }

        return false;
    }

    public int findPakuri(String species) {
        for (int i = 0; i < getSize(); ++i) {
            if (pakudex[i].getSpecies().equals(species)) {
                return i;
            }
        }

        return -1;
    }
}
