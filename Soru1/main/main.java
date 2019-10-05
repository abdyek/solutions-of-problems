package main;

import java.util.ArrayList;
import java.util.Scanner;

public class main {
    static Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        
        System.out.println("Müşteri sayısını giriniz: ");
        int numOfCustomers = scanner.nextInt();
        
        System.out.println("Çalışan sayısını giriniz: ");
        int numOfEmployees = scanner.nextInt();
        
        ArrayList<Person> employees = new ArrayList<Person>(numOfEmployees);
        ArrayList<Person> customers = new ArrayList<Person>(numOfCustomers);
        
        arrangeCustomers(customers, numOfCustomers);
        arrangeEmployees(employees, numOfEmployees);
        
        System.out.println("Hangi veritabanına kaydetmek istersiniz \n1-MySql"
                + "\n2-MsSql \n3-Oracle");
        int database = scanner.nextInt();
        IPersonDal sql;
        switch(database){
            case 1: 
                sql = new MySqlDal();
                sql.add();
                break;
            case 2:
                sql = new MsSqlDal();
                sql.add();
                break;
            case 3:
                sql = new OracleDal();
                sql.add();
                break;
            default:
                System.out.println("Yanlış girdi!");
                break;
        }
        
        while(true){
            System.out.println("1-Müşterileri listele\n2-Çalışanları listele\n3-Çıkış yap");
            int choice = scanner.nextInt();
            switch(choice){
                case 1:
                    printAll(employees);
                    break;
                case 2:
                    printAll(customers);
                    break;
                case 3:
                    return;
            }
        }
    }
    
    static void printAll(ArrayList<Person> person){
        for(int i = 0; i < person.size(); i++){
            Person p = person.get(i);
            System.out.printf("Id: %d, Name: %s, Lastname: %s, Age: %d\n", p.getId(), p.getName(), p.getLastName(), p.getAge());
        }
    }
    
    static void arrangeCustomers(ArrayList<Person> person, int number){
        for(int i = 0; i < number; i++){
            System.out.println("Müşteri id'si: ");
            int id = scanner.nextInt();
            
            System.out.println("Müşteri ismi: ");
            String name = scanner.next();
            
            System.out.println("Müşteri soyismi: ");
            String lastName = scanner.next();
            
            System.out.println("Müşteri yaşı: ");
            int age = scanner.nextInt();
            
            Customer customer = new Customer(id, name, lastName, age);
            person.add(customer);
        }
    }
    
    static void arrangeEmployees(ArrayList<Person> person, int number){
        for(int i = 0; i < number; i++){
            System.out.println("Çalışan id'si: ");
            int id = scanner.nextInt();
            
            System.out.println("Çalışan ismi: ");
            String name = scanner.next();
            
            System.out.println("Çalışan soyismi: ");
            String lastName = scanner.next();
            
            System.out.println("Çalışan yaşı: ");
            int age = scanner.nextInt();
            
            Employee employee = new Employee(id, name, lastName, age);
            person.add(employee);
        }
    }
}
