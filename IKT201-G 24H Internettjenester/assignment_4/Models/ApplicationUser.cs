using Microsoft.AspNetCore.Identity;

namespace assignment_4.Models;

public class ApplicationUser : IdentityUser{

    public string Nickname{ get; set; } = string.Empty;

}