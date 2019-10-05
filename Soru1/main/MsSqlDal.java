
package main;

public class MsSqlDal implements IPersonDal{

    @Override
    public void add() {
        System.out.println("MsSql added");
    }

    @Override
    public void delete() {
        System.out.println("MsSql deleted");
    }

    @Override
    public void update() {
        System.out.println("MsSql updated");
    }
    
}
