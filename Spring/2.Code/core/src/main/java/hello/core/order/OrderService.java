package hello.core.order;

public interface OrderService {
    Order crerateOrder(Long memberId, String itemName, int itemPrice);
}
