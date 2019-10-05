
package main;

public class OracleDal implements IPersonDal{

    @Override
    public void add() {
        System.out.println("Oracle added");
    }

    @Override
    public void delete() {
        System.out.println("Oracle deleted");
    }

    @Override
    public void update() {
        System.out.println("Oracle updated");
    }
    
}
