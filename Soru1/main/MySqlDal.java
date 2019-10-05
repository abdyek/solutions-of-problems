
package main;

public class MySqlDal implements IPersonDal{

    @Override
    public void add() {
        System.out.println("MySql added");
    }

    @Override
    public void delete() {
        System.out.println("MySql deleted");
    }

    @Override
    public void update() {
        System.out.println("MySql updated");
    }
    
}
